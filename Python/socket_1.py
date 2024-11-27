import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = "172.20.241.9"
port = 20000
s.connect((host, port))

s.sendall(b'999\n')


chunks = []
while True:
    data = s.recv(1024)
    if len(data) == 0:
        break
    chunks.append(data.decode('utf-8'))

for i in chunks:
    print(i, end = '')

s.close()
