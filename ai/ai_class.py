from random import randint
from tools import is_a_number
#from connection import ServerConnection

needs_for_lvl_6 = {"linemate": 6,
                   "deraumere": 4,
                   "sibur": 5,
                   "mendiane": 3,
                   "phiras": 3,
                   "thystame": 1}

DEATH_MESSAGE = "AI is dead"

class AI:
    def __init__(self, team, net):
        self.net = net #ServerConnection class
        self.team: str = team
        self.lvl: int = 1
        self.id: int = randint(1, 10000)
        self.dead: bool = False
        self.is_elevating: bool = False
        self.last_eject: int|None = None
        self.random: bool = True
        self.block_k_reception: bool = False
        self.food_supply = False
        self.king: bool = False
        self.choosen_ones: bool = False

        team_slots_left: int = net.send_team(team)
        if (team_slots_left == -1):
            self.dead = True
            return
        self.net.logger.info(f"Team {team} has {team_slots_left} slots left", self.id)

    #---------------------------------#
    #           Send and read         #
    #---------------------------------#

    # Return a dictionary of the inventory
    def inventory(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return None
        response = self.net.send_and_read("Inventory", self)
        inventory: list|None = None
        while (inventory is None):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return None
                if elem.startswith("["):
                    inventory = elem.split("[")[1].split(",")
                else:
                    self.net.add_to_read(elem)
            if inventory is None:
                response = self.net.read(self)
        dic: dict = {}
        if inventory == []:
            return dic
        while inventory[-1][-1] != "]":
            response = self.net.read(self)
            inventory += response.split("\n")[0].split(",")
        for elem in inventory:
            key = elem.split(" ")[1]
            value = int(elem.split(" ")[2])
            dic[key] = value
        return dic
    
    # Look, return a list of the objects around the AI
    def look(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return None
        response: str|None = self.net.send_and_read("Look", self)
        look: list|None = None
        while (look is None):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return None
                if elem.startswith("["):
                    look = elem.split("[")[1].split(",")
                else:
                    self.net.add_to_read(elem)
            if look is None:
                response = self.net.read(self)
        if look == []:
            return None
        while look[-1][-1] != "]":
            response = self.net.read(self)
            look += response.split("\n")[0].split(",")
        for i in range(len(look)):
            look[i] = look[i].split(" ")
        for elem in look:
            for i in range(len(elem) - 1):
                if elem[i] == "":
                    elem.pop(i)
        return look
    
    # Fork the AI
    def fork(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        status: bool = False
        response: str|None = self.net.send_and_read("Fork", self)
        while (not status):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return
                if elem == "ok":
                    status = True
                else:
                    self.net.add_to_read(elem)
            if status is False:
                response = self.net.read(self)
        self.net.logger.info("Forked", self.id)

    # Get the nb of unused slots in the team
    def get_unused_slots(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return -1
        response: str|None = self.net.send_and_read("Connect_nbr", self).split("\n")
        team_slots_left: int = -1
        while (team_slots_left == -1):
            for elem in response:
                if elem == "dead":
                    self.dead = True
                    return -1
                if is_a_number(elem):
                    team_slots_left = int(elem)
                else:
                    self.net.add_to_read(elem)
            if team_slots_left == -1:
                response = self.net.read(self)
        self.net.logger.info(f"Team {self.team} has {team_slots_left} slots left", self.id)
        return team_slots_left
    
    # Incantation
    def incantation(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return False
        response: str|None = self.net.send_and_read("Incantation", self)
        status: bool = False
        while (not status):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return False
                if elem == "ko":
                    self.net.logger.warning("Failed to incant", self.id)
                    return False
                elif elem == "Elevation underway":
                    self.net.add_to_read(elem)
                    status = True
                else:
                    self.net.add_to_read(elem)
            if status is False:
                response = self.net.read(self)
        self.net.logger.info("Incanted", self.id)
        return True

    # Take an object
    def take(self, obj: str):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        response: str|None = self.net.send_and_read(f"Take {obj}", self)
        status: bool = False
        while (not status and not self.dead):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return False
                if elem == "ko":
                    self.net.logger.warning(f"Failed to take {obj}", self.id)
                    return False
                elif elem == "ok":
                    status = True
                else:
                    self.net.add_to_read(elem)
            if status is False:
                response = self.net.read(self)
        self.net.logger.info(f"Took {obj}", self.id)
        return True
    
    # Take all objects on a tile
    def take_all(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        object_list: list|None = self.look()
        if object_list is None or object_list == []:
            return
        object_list = object_list[0]
        for elem in object_list:
            if elem != "player":
                self.take(elem)
    
    def take_all_food(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        object_list: list|None = self.look()
        if object_list is None or object_list == []:
            return
        object_list = object_list[0]
        for elem in object_list:
            if elem == "food":
                self.take(elem)

    def get_nb_player_on_tile(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return -1
        object_list: list|None = self.look()
        if object_list is None or object_list == []:
            return -1
        object_list = object_list[0]
        nb: int = 0
        for elem in object_list:
            if elem == "player":
                nb += 1
        return nb
    
    # Drop an object
    def drop(self, obj: str):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        response: str|None = self.net.send_and_read(f"Set {obj}", self)
        status: bool = False
        while (not status):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return False
                if elem == "ko":
                    self.net.logger.warning(f"Failed to drop {obj}", self.id)
                    return False
                elif elem == "ok":
                    status = True
                else:
                    self.net.add_to_read(elem)
            if status is False:
                response = self.net.read(self)
        self.net.logger.info(f"Dropped {obj}", self.id)
        return True

    def drop_all(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        inv: dict = self.inventory()
        if inv is None:
            return
        for key in inv:
            if key != "food":
                for _ in range(inv[key]):
                    self.drop(key)

    def drop_all_food(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        inv: dict = self.inventory()
        if inv is None:
            return
        for _ in range(inv["food"]):
            self.drop("food")

    def is_inv_empty(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        inv: dict = self.inventory()
        if inv is None:
            return False
        for key in inv:
            if key != "food" and inv[key] > 0:
                return False
        return True
    
    def is_enought_for_lvl(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        inv: dict = self.inventory()
        if inv is None:
            return False
        for key in inv:
            if key != "food" and inv[key] < needs_for_lvl_6[key]:
                return False
        return True
    
    def share_food(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        inv: dict = self.inventory()
        if inv is None:
            return
        leftovers: int = inv["food"] - 15
        if leftovers < 0:
            for _ in range(-leftovers):
                self.take("food")
        else:
            for _ in range(leftovers):
                self.drop("food")

    def get_food_nbr(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return -1
        inv: dict = self.inventory()
        if inv is None:
            return -1
        return inv["food"]

    look_direction: dict = { # moves to reach a position after look
            0: "",
            1: "flf",
            2: "f",
            3: "frf",
            4: "fflff",
            5: "fflf",
            6: "ff",
            7: "ffrf",
            8: "ffrff"
             }
    
    def go_to_obj(self, wanted: str, needs: bool=False):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        object_list: list = self.look()
        if object_list is None or object_list == []:
            return False
        count: int = 0
        for elem in object_list[0]:
            if elem == "player":
                count += 1
        if count > 1:
            self.move_random()
            return False

        pos: int = 0
        found: list = []
        for elem in object_list:
            count = 0
            for obj in elem:
                if obj == wanted:
                    count += 1
            
            if count > 0:
                found.append((pos, count))
            pos += 1
        if len(found) == 0:
            if not needs:
                self.forward()
            return False
        highest: int = 0
        best_pos: int = 0
        for pos, count in found:
            if count > highest:
                highest = count
                best_pos = pos
            if count == highest and len(self.look_direction[pos]) < len(self.look_direction[best_pos]):
                best_pos = pos
        for elem in self.look_direction[best_pos]:
            if elem == "f":
                self.forward()
            elif elem == "r":
                self.turn_right()
            elif elem == "l":
                self.turn_left()
        return True

    def go_to_needs(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        inv: dict = self.inventory()
        if inv is None:
            return
        for key in inv:
            if key != "food" and inv[key] < needs_for_lvl_6[key]:
                if not self.go_to_obj(key, True):
                    continue
                for _ in range(needs_for_lvl_6[key] - inv[key]):
                    self.take(key)
                return
        self.forward()
        
    #---------------------------------#
    #        Send without read        #
    #---------------------------------#

    # Move the AI forward
    def forward(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.send("Forward", self)
        self.net.logger.info("Moved forward", self.id)
    
    # Turn the AI right
    def turn_right(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.send("Right", self)
        self.net.logger.info("Turned right", self.id)

    # Turn the AI left
    def turn_left(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.send("Left", self)
        self.net.logger.info("Turned left", self.id)

    def move_random(self):
        random: int = randint(0, 3)
        match random:
            case 0:
                self.forward()
            case 1:
                self.turn_right()
                self.forward()
            case 2:
                self.turn_left()
                self.forward()

    # Broadcast a message
    def broadcast(self, msg: str):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.send(f"Broadcast {msg}", self)
        self.net.logger.info(f"Broadcasted: {msg}", self.id)
    
    # Eject
    def eject(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.send("Eject", self)
        self.net.logger.info("Ejection sended", self.id)
    
    def go_to_broadcast(self, k: int):
        if (k == 0):
            return

        if (k == 5 ):
            self.turn_right()
            self.turn_right()
        if (k < 5 and k > 1):
            self.turn_left()
        if (k > 5):
            self.turn_right()
        self.forward()
    
    #---------------------------------#
    #        Handle responses         #
    #---------------------------------#

    # Change this function to handle more messages
    def handle_broadcast(self, broadcast_received: str, k: int):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        if self.random and broadcast_received == "lvl6":
            self.random = False
            self.king = False
        if not self.random and broadcast_received == "lvl6":
            self.go_to_broadcast(int(k))
        if broadcast_received == "elevate":
            self.random = False
            if not self.choosen_ones and self.get_nb_player_on_tile() >= 6:
                self.choosen_ones = True
            if self.choosen_ones:
                self.drop_all()
                if self.lvl == 1:
                    self.incantation()
            else:
                self.food_supply = True
