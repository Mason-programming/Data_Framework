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

