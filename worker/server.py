import socket
import os
from worker.inference import predict

SOCKET_PATH = "/tmp/spam_worker.sock"

if os.path.exists(SOCKET_PATH):
    os.remove(SOCKET_PATH)

server = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
server.bind(SOCKET_PATH)
server.listen(5)

print("worker listening on", SOCKET_PATH)

while True:
    conn, _ = server.accept()
    data = conn.recv(4096)
    text = data.decode("utf-8")

    result = predict(text)

    conn.sendall(result.encode("utf-8"))
    conn.close()
