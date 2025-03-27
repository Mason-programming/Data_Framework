import socket
import json

class SceneBusClient:
    def __init__(self, host="localhost", port=8899):
        self.host = host
        self.port = port

    def send_event(self, event_type, data):
        message = json.dumps({"event": event_type, "data": data})
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
                sock.connect((self.host, self.port))
                sock.sendall(message.encode("utf-8"))
        except Exception as e:
            print(f"[SceneBus] Could not send event: {e}")
