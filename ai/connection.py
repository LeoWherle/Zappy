import socket
from messages import server_print, error_print, warning_print, info_print

def connect_to_server(host, port=4242):
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((host, port))
        server_print(sock.recv(1024).decode())
    except Exception as e:
        error_print(f"Failed to connect to server: {e}")
        return None
    return sock

def send_to_server(sock, msg):
    sock.sendall(msg.encode())
    response = sock.recv(1024).decode()
    server_print(response)
    return response

def close_connection(sock):
    sock.close()
    warning_print("Disconnected")
