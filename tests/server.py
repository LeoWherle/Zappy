#!/usr/bin/env python3
import socket
import threading

from typing import List


class Tile:
    def __init__(self, _x=0, _y=0):
        self.food = 0
        self.linemate = 0
        self.deraumere = 0
        self.sibur = 0
        self.mendiane = 0
        self.phiras = 0
        self.thystame = 0
        self.x = _x
        self.y = _y

    def __str__(self):
        return (
            f"bct {self.x} {self.y} {self.food} {self.linemate} {self.deraumere} "
            f"{self.sibur} {self.mendiane} {self.phiras} {self.thystame}\n"
        )


class Map:
    def __init__(self, _x=10, _y=10):
        self.x = _x
        self.y = _y
        self.map = [[Tile(x, y) for x in range(_x)] for y in range(_y)]

    def __str__(self):
        return "".join([str(tile) for row in self.map for tile in row])


class Player:
    def __init__(self, _id, _team):
        self.id = _id
        # L player or incantation level
        self.level = 1
        # N name of the team
        self.team = _team
        self.x = 0
        self.y = 0
        # O orientation: 1(N), 2(E), 3(S), 4(W)
        self.orientation = 0

    def __str__(self):
        return f"pnw {self.id} {self.x} {self.y} {self.orientation} {self.level} {self.team}\n"

    def position(self):
        return f"ppo {self.id} {self.x} {self.y} {self.orientation}\n"

    def level(self):
        return f"plv {self.id} {self.level}\n"


class World:
    def __init__(self, _x=10, _y=10):
        self.x: int = _x
        self.y: int = _y
        self.map: Map = Map(_x, _y)
        self.players: Player = []
        self.teams: str = []

        self.idgen: int = 0

    def add_team(self, team: str):
        """add a team to the world does nothing if the team already exists"""
        if team not in self.teams:
            self.teams.append(team)

    def add_player(self, team: str):
        """add a player to the world with a unique id"""
        self.idgen += 1
        self.players.append(Player(self.idgen, team))

    def msz(self):
        """msz command"""
        return f"msz {self.x} {self.y}\n"

    def bct(self, x, y):
        """bct command"""
        tile = self.map.map[y][x]
        return f"bct {x} {y} {tile.food} {tile.linemate} {tile.deraumere} {tile.sibur} {tile.mendiane} {tile.phiras} {tile.thystame}\n"

    def mct(self):
        """mct command"""
        return "".join([self.bct(x, y) for y in range(self.y) for x in range(self.x)])

    def tna(self):
        """tna command"""
        return "".join([f"tna {team}\n" for team in self.teams])

    def ppo(self, player_id):
        """ppo command"""
        return "".join(
            [player.position() for player in self.players if player.id == player_id]
        )

    def plv(self, player_id):
        """plv command"""
        return "".join(
            [player.level() for player in self.players if player.id == player_id]
        )


class TCPServer:
    def __init__(self, host, port):
        self.host = host
        self.port = port
        self.server_socket = None
        self.zcmd = World()

    def start(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(5)
        print(f"Server listening on {self.host}:{self.port}")

        command_line_thread = threading.Thread(target=self.handle_command_line, args=())
        command_line_thread.start()

        client_socket, client_address = self.server_socket.accept()
        print(f"New connection from {client_address[0]}:{client_address[1]}")

        client_thread = threading.Thread(
            target=self.handle_client, args=(client_socket,)
        )
        client_thread.start()

        command_line_thread.join()
        client_thread.join()

    def handle_command(self, command):
        """
        Handle the command input.
        """
        print(f"Received command: {command}")

    def handle_command_line(self):
        """
        Handle the command line input.
        """
        command = ""
        while True:
            command = input()
            if command == "exit":
                self.server_socket.close()
                break
            else:
                self.handle_command(command)

    def handle_client(self, client_socket):
        """
        Handle the client connection and process the received commands.
        """
        buffer = ""
        client_socket.send("WELCOME\n".encode())
        team_name = client_socket.recv(8).decode()
        if not team_name and team_name != "GRAPHIC\n":
            return
        print(f"Received team name: {team_name}")
        client_socket.send(f"1\n{self.zcmd.x} {self.zcmd.y}\n".encode())
        while True:
            data = client_socket.recv(1024).decode()
            if not data:
                break
            print(f"Received data: {data}")

            buffer += data
            commands = buffer.split("\n")
            buffer = commands.pop()

            for command in commands:
                self.handle_command_net(client_socket, command)
                # if command.endswith("\n"):
                #     print(f"Received command: {command}")

        client_socket.close()

    def handle_command_net(self, client_socket, command):
        command = command.strip()
        cmd = command.split(" ")
        print(f'Got command: "{cmd}"')
        if cmd[0] == "msz":
            print(f"SENT: {self.zcmd.msz()}")
            client_socket.send(self.zcmd.msz().encode())
        elif cmd[0] == "mct":
            client_socket.send(self.zcmd.mct().encode())
        elif cmd[0] == "tna":
            client_socket.send(self.zcmd.tna().encode())
        elif cmd[0] == "ppo":
            player_id = int(cmd[0].split(" ")[1])
            client_socket.send(self.zcmd.ppo(player_id).encode())
        elif cmd[0] == "plv":
            player_id = int(cmd[0].split(" ")[1])
            client_socket.send(self.zcmd.plv(player_id).encode())
        else:
            client_socket.send("ko\n".encode())


if __name__ == "__main__":
    server = TCPServer("localhost", 4242)
    server.start()
