import socket
import threading
from datetime import datetime

server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind(("127.0.0.1", 5000))

print("Time server running...")


def handle_client(addr):

    current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    server.sendto(current_time.encode(), addr)


while True:

    data, addr = server.recvfrom(1024)

    print("Request received from:", addr)

    thread = threading.Thread(
        target=handle_client,
        args=(addr,)
    )

    thread.start()
