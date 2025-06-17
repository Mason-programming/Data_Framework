import sys, os, requests, zipfile, io, shutil
#import bpy
from PySide6.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QLineEdit,
    QPushButton, QLabel, QMessageBox
)
from PySide6.QtCore import QObject, Signal, Slot, QThread, Qt
from PySide6.QtGui import QPixmap

class Pages(QWidget):
    def __init__(self, parent=None):
        super(Pages, self).__init__(parent)
        self.filled = False
        self.asset_name = "Unnamed"

        self.layout = QVBoxLayout()
        self.setLayout(self.layout)

        self.setFixedSize(200, 240)

        # Apply glassy style
        self.setObjectName("assetBlock")
        self.setStyleSheet("""
            #assetBlock {
                background-color: rgba(255, 255, 255, 0.08);
                border-radius: 12px;
                border: 1px solid rgba(255, 255, 255, 0.2);
            }
            #assetBlock:hover {
                background-color: rgba(255, 255, 255, 0.15);
                border: 1px solid rgba(255, 255, 255, 0.35);
            }
        """)

        self.thumbnail_label = QLabel("Waiting...")
        self.thumbnail_label.setFixedSize(160, 160)
        self.thumbnail_label.setAlignment(Qt.AlignCenter)
        self.thumbnail_label.setStyleSheet("""
            QLabel {
                background-color: rgba(255, 255, 255, 0.05);
                border-radius: 6px;
            }
        """)

        self.asset_label = QLabel("Asset Name")
        self.asset_label.setAlignment(Qt.AlignCenter)
        self.asset_label.setStyleSheet("color: white; font-size: 10pt;")

        self.layout.addWidget(self.thumbnail_label)
        self.layout.addWidget(self.asset_label)

    def getIndex(self, index_usda):
        preview_path = index_usda.replace("index.usda", "preview_odie.png")
        self.asset_name = os.path.basename(os.path.dirname(index_usda))
        self.asset_label.setText(self.asset_name)

        if os.path.exists(preview_path):
            pixmap = QPixmap(preview_path).scaled(160, 160, Qt.KeepAspectRatio, Qt.SmoothTransformation)
            self.thumbnail_label.setPixmap(pixmap)
        else:
            self.thumbnail_label.setText("Preview not found")

        self.filled = True

    def mousePressEvent(self, event):
        if self.filled:
            print(f"📦 Placing asset in scene: {self.asset_name}")


class GithubWorker(QObject):
    finished = Signal(str)
    error = Signal(str)

    def __init__(self, link, output_base="downloaded_asset"):
        super().__init__()
        self.link = link
        self.output_base = output_base
        self.asset_index_path = ""

    def convert_to_raw_url(self, url):
        if url.endswith(".usda"):
            return url.replace("github.com", "raw.githubusercontent.com").replace("/blob/", "/")
        elif "github.com" in url and not url.endswith(".zip"):
            parts = url.rstrip("/").split("/")
            if "tree" in parts:
                user, repo, _, branch = parts[3], parts[4], parts[5], parts[6]
                return f"https://github.com/{user}/{repo}/archive/refs/heads/{branch}.zip"
            else:
                user, repo = parts[3], parts[4]
                return f"https://github.com/{user}/{repo}/archive/refs/heads/main.zip"
        return url

    def fetch(self):
        try:
            url = self.convert_to_raw_url(self.link)
            response = requests.get(url)
            response.raise_for_status()

            if url.endswith(".zip"):
                with zipfile.ZipFile(io.BytesIO(response.content)) as z:
                    top_folder = z.namelist()[0].split('/')[0]
                    target_subdir = f"{top_folder}/projects/cp001/assets/odie/"
                    output_dir = self.output_base

                    if os.path.exists(output_dir):
                        shutil.rmtree(output_dir)
                    os.makedirs(output_dir, exist_ok=True)

                    for member in z.namelist():
                        if member.startswith(target_subdir) and not member.endswith("/"):
                            filename = os.path.relpath(member, target_subdir)
                            target_path = os.path.join(output_dir, filename)
                            os.makedirs(os.path.dirname(target_path), exist_ok=True)
                            with open(target_path, 'wb') as f:
                                f.write(z.read(member))

                    self.asset_index_path = os.path.join(output_dir, "index.usda")
                    self.finished.emit(self.asset_index_path)

            elif url.endswith(".usda"):
                filename = url.split("/")[-1]
                with open(filename, "w", encoding="utf-8") as f:
                    f.write(response.text)
                self.asset_index_path = filename
                self.finished.emit(self.asset_index_path)

            else:
                raise ValueError("Unsupported GitHub URL format.")

        except Exception as e:
            self.error.emit(str(e))


class AssetBookInterface(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("Asset Book")
        self.setStyleSheet("background-color: #1e1e1e; color: white;")
        layout = QVBoxLayout()

        self.asset_row = QHBoxLayout()
        self.page_array = []

        for _ in range(3):
            page = Pages()
            self.asset_row.addWidget(page)
            self.page_array.append(page)

        self.status_label = QLabel("Enter GitHub URL to .usda or repo:")
        self.line_edit = QLineEdit(self)
        self.line_edit.setPlaceholderText("https://github.com/...")

        self.fetch_button = QPushButton("Fetch Asset")
        self.fetch_button.clicked.connect(self.run_background_task)

        layout.addLayout(self.asset_row)
        layout.addWidget(self.status_label)
        layout.addWidget(self.line_edit)
        layout.addWidget(self.fetch_button)

        self.setLayout(layout)

    def run_background_task(self):
        url = self.line_edit.text().strip()
        if not url:
            QMessageBox.warning(self, "Error", "Please enter a GitHub URL.")
            return

        self.thread = QThread()
        self.worker = GithubWorker(url)

        self.worker.moveToThread(self.thread)
        self.thread.started.connect(self.worker.fetch)
        self.worker.finished.connect(self.on_fetch_complete)
        self.worker.error.connect(self.on_fetch_error)

        self.worker.finished.connect(self.thread.quit)
        self.worker.finished.connect(self.worker.deleteLater)
        self.thread.finished.connect(self.thread.deleteLater)

        self.thread.start()
        self.status_label.setText("Fetching asset in background...")

    @Slot(str)
    def on_fetch_complete(self, index_path):
        self.status_label.setText(f"Finished: {index_path}")
        print("Pass to backend renderer here ➡", index_path)

        for page in self.page_array:
            if not page.filled:
                page.getIndex(index_path)
                break

    @Slot(str)
    def on_fetch_error(self, error_message):
        QMessageBox.critical(self, "Download Failed", error_message)
        self.status_label.setText("Download failed.")



if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = AssetBookInterface()
    window.show()
    sys.exit(app.exec())