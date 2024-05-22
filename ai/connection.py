import socket

def connect_to_server(host, port=4242):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((host, port))
        print(sock.recv(1024).decode())
    except Exception as e:
        print(f"Failed to connect to server: {e}")
        return None
    return sock

def send_to_server(sock, msg):
    sock.sendall(msg.encode())
    return sock.recv(1024).decode()
