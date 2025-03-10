import sys 
import os 
import psutil

import subprocess 
import time
 

 
DCC_NAME = "Blender"
COMMAND_CENTER_APP_PATH = "/Applications/YourCommandCenter.app"

def is_app_running(app_name):
    for proc in psutil.process_iter(attrs=["name"]):
        if app_name.lower() in proc.info["name"].lower():
            return True
    return False

def show_notification(title, message):
    # Using osascript to send a system notification (macOS)
    script = f'display notification "{message}" with title "{title}"'
    subprocess.run(["osascript", "-e", script])

def main():
    notified = False
    while True:
        if is_app_running(DCC_NAME) and not notified:
            show_notification("🎨 Blender Launched!", "Would you like to open the Command Center?")
            # Optional: Auto-open it for now
            # open_command_center()
            notified = True
        elif not is_app_running(DCC_NAME):
            notified = False
        time.sleep(5)

if __name__ == "__main__":
    main()