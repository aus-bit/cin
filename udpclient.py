import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sentence = input("Enter sentence: ")

s.sendto(sentence.encode(), ("127.0.0.1", 5000))

data, addr = s.recvfrom(1024)

print("Formal English:", data.decode())

s.close()
