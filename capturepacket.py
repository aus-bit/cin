import socket

s = socket.socket(
    socket.AF_PACKET,
    socket.SOCK_RAW,
    socket.ntohs(3)
)

print("Capturing packets...")

while True:

    packet, addr = s.recvfrom(65535)

    print("Packet received")
    print("Source:", addr)

    print("Packet length:", len(packet))
    print("-" * 40)
