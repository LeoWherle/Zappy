import socket

class ServerConnection:
    def __init__(self, logger, host, port=4242):
        self.host = host
        self.port = port
        self.sock = None
        self.map_x = 0
        self.map_y = 0
        self.logger = logger

    # At the start of the program, connect to the server
    def connect(self):
        self.logger.ai("Trying to connect to the server...\n", 0)
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((self.host, self.port))
            self.logger.server(sock.recv(1024).decode(), 0)
        except Exception as e:
            self.logger.error(f"Failed to connect to server: {e}", 0)
            return False
        self.sock = sock
        return True

    def send(self, msg, ai):
        if (msg[-1] != '\n'):
            msg += '\n'
        if (ai == None):
            ai_id = 0
        else:
            ai_id = ai.id
        if (ai != None and ai.dead):
            return
        self.logger.ai(msg, ai_id)
        self.sock.sendall(msg.encode())
        response = self.sock.recv(1024).decode()
        self.logger.server(response, ai_id)
        if response.__contains__("dead"):
            self.logger.warning("The AI is dead", ai_id)
            ai.dead = True
        if response.__contains__("Elevation underway"):
            ai.lvl += 1
            response = self.sock.recv(1024).decode()
            self.logger.server(response, ai_id)
            self.logger.info(f"AI leveled up to {ai.lvl}", ai_id)
        return response
    
    # At the start of the AI, send the team name to the server
    def send_team(self, team):
        infos = self.send(team, None).split("\n")
        if (infos[0] == "ko"):
            self.logger.error(f"No space left in team {team}", -1)
            return -1
        self.map_x = int(infos[1].split(" ")[0])
        self.map_y = int(infos[1].split(" ")[1])
        return int(infos[0])

    # At the end of the program, close the connection
    def close_connection(self):
        self.sock.close()
        self.logger.warning("Disconnected", 0)
