import socket
from messages import logger

class Server:
    def __init__(self, host, port=4242):
        self.host = host
        self.port = port
        self.sock = None
        self.map_x = 0
        self.map_y = 0

    def connect(self):
        logger.ai("Trying to connect to the server...\n")
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((self.host, self.port))
            logger.server(sock.recv(1024).decode())
        except Exception as e:
            logger.error(f"Failed to connect to server: {e}")
            return False
        self.sock = sock
        return True

    def send(self, msg, ai):
        if (msg[-1] != '\n'):
            msg += '\n'
        logger.ai(msg)
        self.sock.sendall(msg.encode())
        response = self.sock.recv(1024).decode()
        logger.server(response)
        if response.__contains__("dead"):
            logger.warning("The AI is dead")
            ai.dead = True
        return response
    
    def send_team(self, team):
        infos = self.send(team, None).split("\n")
        self.map_x = int(infos[1].split(" ")[0])
        self.map_y = int(infos[1].split(" ")[1])
        return int(infos[0])

    def close_connection(self):
        self.sock.close()
        logger.warning("Disconnected")
