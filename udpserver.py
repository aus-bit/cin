import socket

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("127.0.0.1", 5000))

print("Server waiting...")

data, addr = s.recvfrom(1024)

sentence = data.decode()

print("Received:", sentence)

words = {
    "tbh": "to be honest",
    "ig": "I guess",
    "tbf": "to be fair",
    "atm": "at the moment",
    "irl": "in real life",
    "lol": "laughing out loud",
    "asap": "as soon as possible",
    "omg": "oh my god",
    "ttyl": "talk to you later",
    "idk": "I don't know",
    "nvm": "never mind"
}

for short, formal in words.items():
    sentence = sentence.replace(short, formal)

print("Translated:", sentence)

s.sendto(sentence.encode(), addr)

s.close()
