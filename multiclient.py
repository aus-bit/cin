import socket
import threading

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect(("127.0.0.1", 5000))


def receive():

    while True:

        try:
            message = client.recv(1024).decode()
            print("\nOther:", message)

        except:
            break


thread = threading.Thread(target=receive)
thread.start()


while True:

    message = input("You: ")

    client.send(message.encode())
