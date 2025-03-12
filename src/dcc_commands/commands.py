#!/usr/bin/env python3
import os
import subprocess
import sys
import pwd

# Base class for shared utilities
class Commands:
    def __init__(self):
        self.username = pwd.getpwuid(os.getuid()).pw_name
        self.usd_file = self.parse_args()

    def parse_args(self):
        if len(sys.argv) > 1:
            usd_file = sys.argv[1]
            if usd_file.endswith(".usd") and os.path.exists(usd_file):
                return usd_file
            else:
                print("❌ Please provide a valid .usd file path.")
                sys.exit(1)
        return ""

    def save_usd_path(self):
        path_file = f"/Users/{self.username}/Desktop/USD_Bridge/last_usd_path.txt"
        with open(path_file, "w") as f:
            f.write(self.usd_file)

    def base_env(self):
        os.environ["PYTHONPATH"] = f"/Users/{self.username}/Desktop/USD_Bridge/modules:" + os.environ.get("PYTHONPATH", "")
        os.environ["USD_PLUGIN_PATH"] = f"/Users/{self.username}/Desktop/USD_Bridge/plugins"
