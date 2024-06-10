"""
This module provides a ServerConnection class for handling socket communication with a server.
"""
import socket
from messages import Logger
from ai_class import AI

READING_SIZE = 8192

class ServerConnection: # pylint: disable=too-many-instance-attributes
    """
    A class used to represent a Server Connection.

    Attributes
    ----------
    host : str
        a formatted string to print out the host
    port : int
        an integer to represent the port
    sock : socket
        a socket object used for the connection
    map_x : int
        an integer to represent the x-coordinate on the map
    map_y : int
        an integer to represent the y-coordinate on the map
    logger : Logger
        a Logger object to handle logging
    out_buffer : str
        a string buffer for outgoing messages
    in_buffer : str
        a string buffer for incoming messages
    multi_threading : bool
        a boolean to indicate if multi-threading is enabled
    """
    def __init__(self, logger: Logger, host: str, port: int=4242):
        """Initializes ServerConnection with the given parameters."""
        self.host: str = host
        self.port: int = port
        self.sock = None
        self.map_x: int = 0
        self.map_y: int = 0
        self.logger: Logger = logger
        self.out_buffer: str = ""
        self.in_buffer: str = ""
        self.multi_threading: bool = False

    def connect(self):
        """Establishes a connection to the server."""
        self.logger.ai_log("Trying to connect to the server...\n", 0)
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((self.host, self.port))
            self.logger.server_log(sock.recv(READING_SIZE).decode(), 0)
        except Exception as error: # pylint: disable=broad-except
            self.logger.error(f"Failed to connect to server: {error}", 0)
            return False
        self.sock = sock
        self.logger.ai_log("Connected to the server\n", 0)
        return True

    def send_and_read(self, msg: str, ai_instance: AI|None):
        """
        Sends a message to the server and reads the response.

        Parameters:
        msg (str): The message to send.
        ai_instance (AI): The AI instance sending the message.
        """
        self.send_buffer(ai_instance)
        if msg[-1] != '\n':
            msg += '\n'
        if ai_instance is None:
            ai_id = 0
        else:
            ai_id = ai_instance.id
        if ai_instance is not None and ai_instance.dead:
            return None
        self.logger.ai_log(msg, ai_id)
        self.sock.sendall(msg.encode())
        response = self.sock.recv(READING_SIZE).decode()
        if response != "":
            self.logger.server_log(response, ai_id)
            self.add_to_read(response)
        return response

    def send_buffer(self, ai_instance: AI):
        """
        Sends the contents of the input buffer to the server.

        Parameters:
        ai_instance (AI): The AI instance sending the message.
        """
        if ai_instance is None:
            ai_id = 0
        else:
            ai_id = ai_instance.id
        if ai_instance is not None and ai_instance.dead:
            return -1
        for msg in self.in_buffer.split("\n"):
            self.logger.ai_log(msg, ai_id)
        self.sock.sendall(self.in_buffer.encode())
        self.in_buffer = ""
        return ai_id

    def send(self, msg: str, ai_instance: AI):
        """
        Adds a message to the input buffer.

        Parameters:
        msg (str): The message to add.
        """
        if msg[-1] != '\n':
            msg += '\n'
        self.in_buffer += msg
        self.send_buffer(ai_instance)

    def add_to_read(self, response: str):
        """
        Adds a response to the output buffer.

        Parameters:
        response (str): The response to add.
        """
        if response == "":
            return
        if response[-1] != '\n':
            response += '\n'
        self.out_buffer += response

    def read_with_timeout(self):
        """Reads from the socket with a timeout."""
        try:
            response = self.sock.recv(READING_SIZE).decode()
        except TimeoutError:
            return ""
        return response

    def read(self, ai_instance: AI, timeout: bool=False):
        """
        Reads from the socket.

        Parameters:
        ai_instance (AI): The AI instance reading the message.
        timeout (bool): Whether to use a timeout when reading.
        """
        if timeout:
            self.sock.settimeout(0.1)
            response = self.read_with_timeout()
            self.sock.settimeout(None)
        else:
            response = self.sock.recv(READING_SIZE).decode()
        if response != "":
            self.logger.server_log(response, ai_instance.id)
            self.add_to_read(response)
        return response

    def empty_buffer(self, ai_instance: AI):
        """
        Empties the output buffer.

        Parameters:
        ai_instance (AI): The AI instance.
        """
        ai_instance.net.read(ai_instance, timeout=True)
        for elem in self.out_buffer.split("\n"):
            if elem == "dead":
                ai_instance.dead = True
                self.logger.warning("The AI is dead", ai_instance.id)
                self.out_buffer = ""
                return
            if elem.startswith("Current level"):
                ai_instance.lvl = int(elem.split(":")[1])
                self.logger.server_log(elem, ai_instance.id)
                self.logger.info(f"AI leveled up to {ai_instance.lvl}", ai_instance.id)
                ai_instance.is_elevating = False
                if ai_instance.lvl == 8:
                    return
            if elem.startswith("eject"):
                ai_instance.last_eject = int(elem.split(":")[1])
                self.logger.info(f"Ejected: K = {ai_instance.last_eject}", ai_instance.id)
            if elem.startswith("message") and not ai_instance.block_k_reception:
                k = elem.removeprefix("message ").split(",")[0]
                message = elem.split(",")[1].removeprefix(" ")
                self.logger.info(f"Received broadcast K = {k}: {message}", ai_instance.id)
                ai_instance.handle_broadcast(message, k)
                ai_instance.block_k_reception = True
            if elem == "Elevation underway":
                ai_instance.is_elevating = True

        self.out_buffer = ""
        ai_instance.block_k_reception = False

    def send_team(self, team: str):
        """
        Sends the team name to the server.

        Parameters:
        team (str): The team name.
        """
        response = self.send_and_read(team, None)
        if response.split("\n")[0] == "ko":
            self.logger.warning(f"No space left in team {team}", -1)
            return -1
        infos = response.split("\n")
        coord = infos[1].split(" ")
        self.map_x = int(coord[0])
        self.map_y = int(coord[1])
        return int(infos[0])

    def close_connection(self, ai_instance: AI):
        """Closes the connection to the server."""
        self.sock.close()
        self.logger.warning("Disconnected", ai_instance.id)
