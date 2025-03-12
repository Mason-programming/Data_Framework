#!/usr/bin/env python3
import os
import sys
import pwd
import subprocess

# Add USD_Bridge/src to PYTHONPATH
real_script_path = os.path.realpath(__file__)
project_root = os.path.abspath(os.path.join(os.path.dirname(real_script_path), ".."))
src_path = os.path.join(project_root, "src")
sys.path.insert(0, src_path)

from dcc_commands.commands import Commands

class UnrealLauncher(Commands):
    def __init__(self):
        super().__init__()
        self.unreal_binary_path = os.path.join("/Users/Shared", "Epic Games", "UE_5.4", "Engine", "Binaries", "Mac", "UnrealEditor")
        self.bridge_script = f"/Users/{self.username}/Desktop/USD_Bridge/src/run_in_unreal.py"
        self.usd_file = ""
        self.root_project = ""

    def parse_args(self):
        if len(sys.argv) < 3:
            print("Usage: dounreal <usd_file.usd> <UnrealProjectName>")
            sys.exit(1)

        self.usd_file = sys.argv[1]
        self.root_project = sys.argv[2]

        if not self.usd_file.endswith(".usd") or not os.path.exists(self.usd_file):
            print("Please provide a valid USD file.")
            sys.exit(1)

    def load_env(self, username):
        os.environ["UE_PROJECT_ROOT"] = os.path.join("/Users", self.username, "Documents", "Unreal Projects", self.root_project)
        os.environ["USD_FILE_PATH"] = self.usd_file

    def launch_unreal(self):
        project_path = os.path.join(os.environ.get("UE_PROJECT_ROOT"), f"{self.root_project}.uproject")

        if os.path.exists(project_path):
            command = [
                self.unreal_binary_path,
                project_path,
                f"-ExecutePythonScript={self.bridge_script}"
            ]
            try:
                subprocess.Popen(
                    command,
                    stdout=subprocess.DEVNULL,
                    stderr=subprocess.DEVNULL,
                    stdin=subprocess.DEVNULL,
                    start_new_session=True
                )
                print(f"✅ Unreal launched with project {self.root_project} and ran {self.bridge_script}")
            except Exception as e:
                print(f"🚨 Failed to launch Unreal: {e}")
        else:
            print(f"❌ The path {project_path} does not exist")
            sys.exit(1)

if __name__ == "__main__":
    do_unreal = UnrealLauncher()
    user_id = os.getuid()
    username = pwd.getpwuid(user_id).pw_name
    do_unreal.parse_args()
    do_unreal.load_env(username)
    do_unreal.launch_unreal()
