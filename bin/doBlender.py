#!/usr/bin/env python3
import os 
import subprocess 
import sys 
import pwd 
import json 


def args(): 
    pass 



def load_envos(username): 

    # Set env vars before launching Blender
    os.environ["BLENDER_USE_USD"] = "1"
    os.environ["PYTHONPATH"] = f"/Users/{username}/Desktop/USD_Bridge/modules:" + os.environ.get("PYTHONPATH", "")
    os.environ["USD_PLUGIN_PATH"] = f"/Users/{username}/Desktop/USD_Bridge/plugins"

def launch_blender(BLENDER_PATH,BRIDGE_SCRIPT,args): 


    command = [

    BLENDER_PATH,
    "--python", BRIDGE_SCRIPT, args

    ]

    subprocess.run(command)    


if __name__=="__main__": 
    username = os.getuid()
    gather_args = args() 

    BLENDER_PATH = "/Applications/Blender.app/Contents/MacOS/Blender"
    BRIDGE_SCRIPT = f"/Users/{username}/Desktop/USD_Bridge/src/run_in_blender.py"

    load_envos(username) 

    launch_blender(BLENDER_PATH, BRIDGE_SCRIPT, gather_args)

