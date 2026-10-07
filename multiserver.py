import socket
import threading

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(("127.0.0.1", 5000))
server.listen(5)

clients = []

def handle_client(conn, addr):

    print("Connected:", addr)

    while True:

        try:
            message = conn.recv(1024).decode()

            if not message:
                break

            print(addr, ":", message)

            for client in clients:
                if client != conn:
                    client.send(message.encode())

        except:
            break

    clients.remove(conn)
    conn.close()


while True:

    conn, addr = server.accept()

    clients.append(conn)

    thread = threading.Thread(
        target=handle_client,
        args=(conn, addr)
    )

    thread.start()
