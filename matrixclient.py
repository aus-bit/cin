import socket
import random

# Create TCP socket
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to server
client.connect(("127.0.0.1", 5000))

# Input matrix order
n = int(input("Enter the order of matrix: "))

# Send N to server
client.send(str(n).encode())

# Create matrix with random numbers from 1 to 50
matrix = []

for i in range(n):
    row = []
    for j in range(n):
        row.append(random.randint(1, 50))
    matrix.append(row)

# Display matrix
print("\nGenerated Matrix:")
for row in matrix:
    print(row)

# Send matrix row by row
for row in matrix:
    data = " ".join(map(str, row))
    client.send(data.encode())

# Receive result
result = client.recv(1024).decode()

# Display result
print("\nMatrix Type:", result)

# Close socket
client.close()
