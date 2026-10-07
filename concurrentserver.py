import socket
import threading
import os

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind(("127.0.0.1", 5000))
server.listen(5)

print("File server running...")


def handle_client(conn, addr):

    filename = conn.recv(1024).decode()

    pid = os.getpid()

    if os.path.exists(filename):

        with open(filename, "r") as file:
            content = file.read()

        result = "PID: " + str(pid) + "\n" + content

    else:

        result = "PID: " + str(pid) + "\nFile not found"

    conn.send(result.encode())

    conn.close()


while True:

    conn, addr = server.accept()

    thread = threading.Thread(
        target=handle_client,
        args=(conn, addr)
    )

    thread.start()
