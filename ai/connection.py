import socket

class ServerConnection:
    def __init__(self, logger, host, port=4242):
        self.host = host
        self.port = port
        self.sock = None
        self.map_x = 0
        self.map_y = 0
        self.logger = logger
        self.out_buffer = ""
        self.in_buffer = ""
        self.multi_threading = False

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

    def send_and_read(self, msg, ai):
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
        if (response != ""):
            self.logger.server(response, ai_id)
            self.add_to_read(response)
        return response
    
    def send_buffer(self, ai):
        if (ai == None):
            ai_id = 0
        else:
            ai_id = ai.id
        if (ai != None and ai.dead):
            return
        for msg in self.in_buffer.split("\n"):
            self.logger.ai(msg, ai_id)
        self.sock.sendall(self.in_buffer.encode())
        self.in_buffer = ""
        return ai_id
    
    def add_to_send(self, msg):
        if (msg[-1] != '\n'):
            msg += '\n'
        self.in_buffer += msg

    def add_to_read(self, response):
        self.out_buffer += response

    def read_with_timeout(self):
        try:
            response = self.sock.recv(1024).decode()
        except TimeoutError:
            return ""
        return response

    def read(self, ai, timeout=False):
        if (timeout):
            self.sock.settimeout(0.1)
            response = self.read_with_timeout()
            self.sock.settimeout(None)
        else:
            response = self.sock.recv(1024).decode()
        if (response != ""):
            self.logger.server(response, ai.id)
            self.add_to_read(response)
        return response
    
    def empty_buffer(self, ai):
        ai.net.read(ai, timeout=True)
        for elem in self.out_buffer.split("\n"):
            if elem == "dead":
                ai.dead = True
                self.logger.warning("The AI is dead", ai.id)
                self.out_buffer = ""
                return
            if elem.startswith("Current level"):
                ai.lvl = int(elem.split(":")[1])
                self.logger.server(elem, ai.id)
                self.logger.info(f"AI leveled up to {ai.lvl}", ai.id)
                ai.is_elevating = False
            if elem.startswith("eject"):
                ai.last_eject = int(elem.split(":")[1])
                self.logger.info(f"Ejected: K = {ai.last_eject}", ai.id)
            if elem.startswith("message"):
                k = elem.removeprefix("message ").split(",")[0]
                message = elem.split(",")[1].removeprefix(" ")
                self.logger.info(f"Received broadcast K = {k}: {message}", ai.id)
                ai.handle_broadcast(message, k)
            if elem == "Elevation underway":
                ai.is_elevating = True

        self.out_buffer = ""

    
    # At the start of the AI, send the team name to the server
    def send_team(self, team):
        response = self.send_and_read(team, None)
        for elem in response.split("\n"):
            if elem == "ko":
                self.logger.warning(f"No space left in team {team}", -1)
                return -1
            else:
                infos = response.split("\n")
                break
        coord = infos[1].split(" ")
        self.map_x = int(coord[0])
        self.map_y = int(coord[1])
        return int(infos[0])

    # At the end of the program, close the connection
    def close_connection(self):
        self.sock.close()
        self.logger.warning("Disconnected", 0)
