#!/usr/bin/env python3
import os
import subprocess
import sys

# Dynamically find the absolute path to the repo root and src directory
current_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.abspath(os.path.join(current_dir, ".."))
src_path = os.path.join(project_root, "src")

# Add src to PYTHONPATH
sys.path.insert(0, src_path)
from bridge_scripts.sessionManager import sessionManager

# Blender-specific subclass
class BlenderLauncher(sessionManager):
    def __init__(self):
        super().__init__()
        self.blender_path = "/Applications/Blender.app/Contents/MacOS/Blender"
        self.bridge_script = "/Users/masonkirby/Desktop/Data_Framework/src/bridge_scripts/run_in_blender.py"
        os.environ["BLENDER_USE_USD"] = "1"

        try:
            self.launch(self.blender_path, self.bridge_script, sys.argv)
        except Exception as e:
            print(f"Failed to launch Blender: {e}")

if __name__ == "__main__":
    launcher = BlenderLauncher()
