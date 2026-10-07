import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

message = "TIME"

client.sendto(
    message.encode(),
    ("127.0.0.1", 5000)
)

data, addr = client.recvfrom(1024)

print("Server Time:", data.decode())

client.close()
