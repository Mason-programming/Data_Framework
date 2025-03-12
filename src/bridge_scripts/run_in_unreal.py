import unreal
import socket
import threading
import os
import queue

# Queue to hold socket commands safely
command_queue = queue.Queue()

def import_usd_file(usd_path):
    if not os.path.exists(usd_path):
        unreal.log_warning(f"⚠️ USD file not found: {usd_path}")
        return

    options = unreal.UsdStageImportOptions()
    options.import_materials = True
    options.import_textures = True
    options.import_meshes = True

    importer = unreal.UsdImporter()
    try:
        result = importer.import_from_file(usd_path, "/Game/USD", options)
        if result:
            unreal.log(f"✅ Successfully imported: {usd_path}")
        else:
            unreal.log_error(f"❌ Failed to import: {usd_path}")
    except Exception as e:
        unreal.log_error(f"🚨 Exception during USD import: {e}")

def handle_command(data):
    if data.startswith("IMPORT_USD:"):
        usd_path = data.split(":", 1)[1].strip()
        command_queue.put(usd_path)
    else:
        unreal.log_warning(f"Unknown command received: {data}")

def start_socket_listener():
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind(("localhost", 5567))
        server.listen(1)
        print("📡 Unreal socket listener active on port 5567")

        while True:
            conn, _ = server.accept()
            data = conn.recv(1024).decode("utf-8")
            handle_command(data)
            conn.close()
    except Exception as e:
        print(f"Socket listener error: {e}")

def process_queue():
    if not command_queue.empty():
        usd_path = command_queue.get()
        import_usd_file(usd_path)

# Start the listener thread (no Unreal API calls here!)
threading.Thread(target=start_socket_listener, daemon=True).start()

# Use Unreal timer to safely check the queue on the main thread
unreal.log("🎬 Starting USD socket polling...")
unreal.SystemLibrary.set_timer(lambda: process_queue(), 1.0, True)
