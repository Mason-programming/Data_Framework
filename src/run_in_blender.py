# run_in_blender.py (inside Blender GUI)
import bpy
import socket
import threading

import os
usd_file = os.environ.get("USD_FILE_PATH")
if usd_file:
    bpy.ops.wm.usd_import(filepath=usd_file)
    print(f"📥 Imported {usd_file}")

def handle_command(data):
    if data.startswith("IMPORT_USD"):
        path = data.split(":", 1)[1].strip()
        bpy.ops.wm.usd_import(filepath=path)
        print(f"✅ Blender imported: {path}")

def start_socket_listener():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("localhost", 5566))
    server.listen(1)
    print("🧠 Blender listening on port 5566...")
    while True:
        conn, _ = server.accept()
        data = conn.recv(1024).decode("utf-8")
        handle_command(data)
        conn.close()

threading.Thread(target=start_socket_listener, daemon=True).start()
