import os
import time
import socket
import subprocess
import psutil

# Supported DCCs
DCC_NAMES = ["blender", "maya", "unreal", "houdini"]

# Friendly display names
DISPLAY_NAMES = {
    "blender": "Blender",
    "maya": "Maya",
    "unreal": "Unreal",
    "houdini": "Houdini"
}

# Path to saved USD
def get_last_usd_path():
    path = os.path.expanduser("~/Desktop/USD_Bridge/last_usd_path.txt")
    if os.path.exists(path):
        with open(path, "r") as f:
            usd = f.read().strip()
            if os.path.exists(usd):
                return usd
            else:
                print("⚠️ USD file does not exist.")
    return None

def is_dcc_running(dcc_name):
    for proc in psutil.process_iter(attrs=["name"]):
        try:
            if dcc_name.lower() in proc.info["name"].lower():
                return True
        except (psutil.NoSuchProcess, psutil.AccessDenied):
            continue
    return False

def show_notification(dcc, usd_path):
    title = f"{DISPLAY_NAMES[dcc]} Launched 🚀"
    message = f"Click to load {usd_path} "
    command = f'display notification "{message}" with title "{title}"'
    process = subprocess.run(["osascript", "-e", command], capture_output=True, text=True)

    print(process.returncode)

def send_usd_to_blender_via_socket(usd_path):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect(("localhost", 5566))  # Blender socket server
            s.sendall(f"IMPORT_USD:{usd_path}".encode("utf-8"))
            print(f"✅ Sent USD to Blender: {usd_path}")
    except ConnectionRefusedError:
        print("❌ Blender listener not active. Is the socket server running in Blender?")

def send_usd_to_unreal_via_socket(usd_path):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect(("localhost", 5566))  # Blender socket server
            s.sendall(f"IMPORT_USD:{usd_path}".encode("utf-8"))
            print(f"✅ Sent USD to unreal: {usd_path}")
    except ConnectionRefusedError:
        print("❌ Blender listener not active. Is the socket server running in Blender?")

def open_usd_in_dcc(dcc, usd_path):
    if not usd_path:
        return
    if dcc == "blender":
        send_usd_to_blender_via_socket(usd_path)
    elif dcc == "unreal": 
        send_usd_to_unreal_via_socket(usd_path)
    elif dcc == "unity": 
        pass 
    elif dcc == "maya": 
        pass
    else:
        print(f"USD auto-load not implemented for {dcc}")

def main():
    print("🔍 Watching for DCC launches...")
    notified_dccs = set()
    usd_path = get_last_usd_path() 

    while True:
        for dcc in DCC_NAMES:
            if is_dcc_running(dcc) and dcc not in notified_dccs:
                show_notification(dcc, usd_path)
                open_usd_in_dcc(dcc, usd_path)
                notified_dccs.add(dcc)
        time.sleep(5)

if __name__ == "__main__":
    main()
