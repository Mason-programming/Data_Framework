import os
import sys
import json
import os.path
import socket
import subprocess
from pxr import Usd
from bridge_scripts.SharedDataClient import SharedDataClient

sys.path.insert(0, os.path.abspath("src"))


_current_session = None

def get_manager():
    global _current_session
    if _current_session is None:
        _current_session = sessionManager()
    return _current_session
class sessionManager(SharedDataClient):
    def __init__(self):
        super().__init__()
        self.storage = None
        self.stage = None
    def get_usd_file(self, usd_scene):

        if os.path.isdir(usd_scene):
            usd_file = self.find_stage(usd_scene)
            return usd_file

        if usd_scene.endswith(".usd") or usd_scene.endswith(".usda") and os.path.exists(usd_scene):
            return usd_scene
        else:
            print("Please provide a valid .usd file path.")
            sys.exit(1)
        return ""

    def find_stage(self, usd_scene):
        for path, directories, files in os.walk(usd_scene):

            if type(files) is list:

                for file in files:
                    if file.endswith(".usd") or file.endswith(".usda"):
                        return os.path.join(path, file)
            else:
                return os.path.join(path, files)

        return None

    def launch(self, path_to_dcc, bridge_script=None, argv=None):
        usd_file = None

        if argv and len(argv) > 1:
            usd_file = self.get_usd_file(argv[1])
            self.storage = usd_file

        if self.storage:
            self.stage = Usd.Stage.Open(self.storage)
            self._add_entry("Blender", self.storage)

        project_root = "/Users/masonkirby/Desktop/Data_Framework/"

        env = os.environ.copy()

        build_dir = os.path.join(project_root, "cmake-build-debug")
        existing_path = env.get("PYTHONPATH", "")
        env["PYTHONPATH"] = f"{build_dir}:{existing_path}"

        if usd_file:
            env["USD_FILE_PATH"] = usd_file

        # Confirm it's correct before launching
        print(f"Launching Blender with PYTHONPATH: {env['PYTHONPATH']}")

        process = subprocess.Popen(
            [path_to_dcc, "--python", bridge_script],
            start_new_session=True,
            env=env
        )

    def get_current_stage(self):
        self.storage = self.get_entry("Blender")
        try:
            self.stage = Usd.Stage.Open(list(self.storage.values())[0])
            return self.stage
        except Exception as e:
            print("Could not grab current stage")
            return None

    def load_usd(self, usd_file):
        try:
            self.storage = usd_file
            self.stage = Usd.Stage.Open(usd_file)
        except Exception as e:
            print(e)

    def _add_entry(self, session_name, usd_file):
        self.add_entry(session_name,usd_file)

    def _get_entry(self):
        return self.stage.GetEntry()

    def _remove_entry(self):
        pass