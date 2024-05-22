import socket
from messages import logger

class Server:
    def __init__(self, host, port=4242):
        self.host = host
        self.port = port
        self.sock = None

    def connect(self):
        logger.ai("Trying to connect to the server...")
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((self.host, self.port))
            logger.server(sock.recv(1024).decode())
        except Exception as e:
            logger.error(f"Failed to connect to server: {e}")
            return False
        self.sock = sock
        return True

    def send(self, msg):
        if (msg[-1] != '\n'):
            msg += '\n'
        logger.ai(msg)
        self.sock.sendall(msg.encode())
        response = self.sock.recv(1024).decode()
        logger.server(response)
        return response

    def close_connection(self):
        self.sock.close()
        logger.warning("Disconnected")
