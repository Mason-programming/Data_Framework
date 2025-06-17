import json
import socket
class SharedDataClient:
    def _send(self, msg):
        with socket.create_connection(("localhost", 7777)) as sock:
            sock.sendall(json.dumps(msg).encode())
            return json.loads(sock.recv(4096).decode())

    def add_entry(self,session_name, usd_path):
        return self._send({"cmd": "addEntry", "sessionName": session_name, "usdFile": usd_path})

    def get_entry(self, session_name):
        return self._send({"cmd": "getEntry", "sessionName": session_name})

    def remove_entry(self, pid):
        return self._send({"cmd": "removeEntry", "pid": pid})
