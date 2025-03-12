#!/usr/bin/env python3
import os 
import subprocess 
import sys 

# Dynamically add the path to the src directory
current_dir = os.path.dirname(os.path.abspath(__file__))
src_path = os.path.abspath(os.path.join(current_dir, "..", "src"))
sys.path.append(src_path)

# Now you can import your base class
from dcc_commands import commands


# Blender-specific subclass
class BlenderLauncher(Commands):
    def __init__(self):
        super().__init__()
        self.blender_path = "/Applications/Blender.app/Contents/MacOS/Blender"
        self.bridge_script = f"/Users/{self.username}/Desktop/USD_Bridge/src/run_in_blender.py"

    def load_env(self):
        os.environ["BLENDER_USE_USD"] = "1"
        if self.usd_file:
            os.environ["USD_FILE_PATH"] = self.usd_file

    def launch_blender(self):
        command = [
            self.blender_path,
            "--python", self.bridge_script
        ]
        try:
            subprocess.Popen(
                command,
                stdout=subprocess.DEVNULL,
                stderr=subprocess.DEVNULL,
                stdin=subprocess.DEVNULL,
                start_new_session=True
            )
            print("🎬 Blender launched and listening on port 5566.")
        except Exception as e:
            print(f"🚨 Failed to launch Blender: {e}")

if __name__ == "__main__":
    do_blender = BlenderLauncher()
    do_blender.base_env()
    do_blender.load_env()
    do_blender.launch_blender()
    if do_blender.usd_file:
        do_blender.save_usd_path()
