#!/usr/bin/env python3
import os 
import subprocess 
import sys 
import pwd 
import json 

def args(): 

    if len(sys.argv) > 1: 
        usd_file = sys.argv[1]
        if usd_file.endswith(".usd") and os.path.exists(usd_file):
            return usd_file
        else:
            print("❌ Please provide a valid .usd file path.")
            sys.exit(1)
    else:
        return 

def save_usd_path(usd_file, username):
    path_file = f"/Users/{username}/Desktop/USD_Bridge/last_usd_path.txt"
    with open(path_file, "w") as f:
        f.write(usd_file)

def load_envos(username, args): 

    # Set env vars before launching Blender
    os.environ["BLENDER_USE_USD"] = "1"
    os.environ["PYTHONPATH"] = f"/Users/{username}/Desktop/USD_Bridge/modules:" + os.environ.get("PYTHONPATH", "")
    os.environ["USD_PLUGIN_PATH"] = f"/Users/{username}/Desktop/USD_Bridge/plugins"
    if len(args) != 0: 
        os.environ["USD_FILE_PATH"] = args

def launch_blender(BLENDER_PATH,BRIDGE_SCRIPT,args): 

    command = [

    BLENDER_PATH,
    "--python", BRIDGE_SCRIPT
    ]

    try: 
        # Launch in detached mode (no terminal blocking)
        subprocess.Popen(
            command,
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            stdin=subprocess.DEVNULL,
            start_new_session=True  # Fully detached from parent shell
        )
        print("Listening on post 5566")
    except: 
        pass 

if __name__=="__main__": 
    user_id = os.getuid()
    username = pwd.getpwuid(user_id).pw_name
    gather_args = args() 

    BLENDER_PATH = "/Applications/Blender.app/Contents/MacOS/Blender"
    BRIDGE_SCRIPT = f"/Users/{username}/Desktop/USD_Bridge/src/run_in_blender.py"

    load_envos(username, gather_args) 

    launch_blender(BLENDER_PATH, BRIDGE_SCRIPT, gather_args)

    save_usd_path(gather_args, username)

