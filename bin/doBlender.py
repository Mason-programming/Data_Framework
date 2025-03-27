#!/usr/bin/env python3
import os
import sys
import subprocess 
from processbridge import ProcessCommand


# Dynamically find the absolute path to the repo root and src directory
current_dir = os.path.dirname(os.path.abspath(__file__))
project_root = os.path.abspath(os.path.join(current_dir, ".."))
src_path = os.path.join(project_root, "src")

# Add src to PYTHONPATH
sys.path.insert(0, src_path)

from dcc_commands.commands import Commands

# Blender-specific subclass
class BlenderLauncher(Commands):
    def __init__(self):
        super().__init__()
        self.blender_path = "/Applications/Blender.app/Contents/MacOS/Blender"
        self.bridge_script = f"/Users/{self.username}/Desktop/USD_Bridge/src/bridge_scripts/run_in_blender.py"
        os.environ["BLENDER_USE_USD"] = "1"
        
    def launch_blender(self):
        try: 
            cmd = ProcessCommand(self.blender_path, self.usd_file, "layout")
            cmd.launch()
            print(self.bridge_script) 

        except Exception as e:
            print(f"Failed to launch Blender: {e}")

        info = cmd.getProcessInfo()
        print(info)

    
        

if __name__ == "__main__":
    do_blender = BlenderLauncher()
    do_blender.base_env()
    do_blender.launch_blender()
    if do_blender.usd_file:
        do_blender.save_usd_path()
