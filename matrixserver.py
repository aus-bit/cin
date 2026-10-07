import socket

# Create TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind server to IP address and port
server.bind(("127.0.0.1", 5000))

# Wait for client
server.listen(1)

print("Server is waiting for client...")

# Accept client connection
conn, addr = server.accept()

print("Client connected:", addr)

# Receive matrix size
n = int(conn.recv(1024).decode())

# Receive matrix
matrix = []

for i in range(n):
    row = list(map(int, conn.recv(1024).decode().split()))
    matrix.append(row)

print("Matrix received:")
for row in matrix:
    print(row)

# Check diagonal
diagonal = True
for i in range(n):
    for j in range(n):
        if i != j and matrix[i][j] != 0:
            diagonal = False

# Check upper triangular
upper = True
for i in range(n):
    for j in range(i):
        if matrix[i][j] != 0:
            upper = False

# Check lower triangular
lower = True
for i in range(n):
    for j in range(i + 1, n):
        if matrix[i][j] != 0:
            lower = False

# Identify matrix type
if diagonal:
    result = "Diagonal Matrix"
elif upper:
    result = "Upper Triangular Matrix"
elif lower:
    result = "Lower Triangular Matrix"
else:
    result = "None of these"

# Send result to client
conn.send(result.encode())

print("Result sent:", result)

# Close sockets
conn.close()
server.close()
