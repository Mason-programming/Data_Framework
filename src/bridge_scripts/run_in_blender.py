import bpy
import threading
import os
import socket

PORT = 5566

# Import if USD file provided via env
usd_file = os.environ.get("USD_FILE_PATH")
if usd_file and os.path.exists(usd_file):
    bpy.ops.wm.usd_import(filepath=usd_file)
    print(f"📥 Imported {usd_file}")

def handle_command(data):
    print(f"🔄 Received command: {data}")
    if data.startswith("IMPORT_USD:"):
        path = data.split(":", 1)[1].strip()
        if os.path.exists(path):
            bpy.ops.wm.usd_import(filepath=path)
            print(f"📥 Re-imported {path}")
        else:
            print(f"❌ USD file not found: {path}")

def start_socket_listener():
    try:
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind(("0.0.0.0", PORT))
        print(f"✅ Socket bound to localhost:{PORT}")
        server.listen(1)
        print("🧠 Blender listening on port 5566...")
        while True:
            conn, _ = server.accept()
            data = conn.recv(1024).decode("utf-8")
            handle_command(data)
            conn.close()
    except Exception as e:
        print(f"🔥 Socket error: {e}")

# Launch socket listener in background thread
thread = threading.Thread(target=start_socket_listener, daemon=True)
thread.start()
print("🔌 Socket listener started")

