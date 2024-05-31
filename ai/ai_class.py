import threading
from random import randint
from tools import is_a_number

needs_for_lvl_6 = {"linemate": 6,
                   "deraumere": 4,
                   "sibur": 5,
                   "mendiane": 3,
                   "phiras": 3,
                   "thystame": 0}

DEATH_MESSAGE = "AI is dead"

class AI:
    def __init__(self, team, net):
        self.net = net
        self.team = team
        self.lvl = 1
        self.id = randint(1, 10000)
        self.dead = False
        self.is_elevating = False
        self.last_eject = None
        self.random = True
        self.block_k_reception = False
        self.food_supply = False
        self.king = False
        self.choosen_ones = False

        team_slots_left = net.send_team(team)
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
        inventory = None
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
        dic = {}
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
        response = self.net.send_and_read("Look", self)
        look = None
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
        look.pop(-1)
        return look
    
    # Fork the AI
    def fork(self, func, args, threads):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        status = False
        response = self.net.send_and_read("Fork", self)
        while (not status):
            for elem in response.split("\n"):
                if elem == "dead":
                    self.dead = True
                    return
                if elem == "ok":
                    status = True
                else:
                    self.net.add_to_read(elem)
            if status == False:
                response = self.net.read(self)
        self.net.logger.info("Forked", self.id)
        if (not self.net.multi_threading):
            self.net.logger.info("Mutli threading is disabled, manually connect an AI", self.id)
        else:
            threads.append(threading.Thread(target=func, args=args))
            threads[-1].start()

    # Get the nb of unused slots in the team
    def get_unused_slots(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return -1
        response = self.net.send_and_read("Connect_nbr", self).split("\n")
        team_slots_left = -1
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
        response = self.net.send_and_read("Incantation", self)
        status = False
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
            if status == False:
                response = self.net.read(self)
        self.net.logger.info("Incanted", self.id)
        return True

    # Take an object
    def take(self, obj):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        response = self.net.send_and_read(f"Take {obj}", self)
        status = False
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
            if status == False:
                response = self.net.read(self)
        self.net.logger.info(f"Took {obj}", self.id)
        return True
    
    # Take all objects on a tile
    def take_all(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        object_list = self.look()
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
        object_list = self.look()
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
        object_list = self.look()
        if object_list is None or object_list == []:
            return -1
        object_list = object_list[0]
        nb = 0
        for elem in object_list:
            if elem == "player":
                nb += 1
        return nb
    
    # Drop an object
    def drop(self, obj):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        response = self.net.send_and_read(f"Set {obj}", self)
        status = False
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
            if status == False:
                response = self.net.read(self)
        self.net.logger.info(f"Dropped {obj}", self.id)
        return True

    def drop_all(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        inv = self.inventory()
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
        inv = self.inventory()
        if inv is None:
            return
        for _ in range(inv["food"]):
            self.drop("food")

    def is_inv_empty(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        inv = self.inventory()
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
        inv = self.inventory()
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
        inv = self.inventory()
        if inv is None:
            return
        leftovers = inv["food"] - 15
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
        inv = self.inventory()
        if inv is None:
            return -1
        return inv["food"]
    
    #---------------------------------#
    #        Send without read        #
    #---------------------------------#

    # Move the AI forward
    def forward(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.add_to_send("Forward")
        self.net.logger.info("Moved forward", self.id)
    
    # Turn the AI right
    def turn_right(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.add_to_send("Right")
        self.net.logger.info("Turned right", self.id)

    # Turn the AI left
    def turn_left(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.add_to_send("Left")
        self.net.logger.info("Turned left", self.id)

    def move_random(self):
        random = randint(0, 3)
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
    def broadcast(self, msg):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.add_to_send(f"Broadcast {msg}")
        self.net.logger.info(f"Broadcasted: {msg}", self.id)
    
    # Eject
    def eject(self):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        self.net.add_to_send("Eject")
        self.net.logger.info("Ejection sended", self.id)
    
    def go_to_broadcast(self, k):
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
    def handle_broadcast(self, broadcast_received, k):
        if (self.dead):
            self.net.logger.warning(DEATH_MESSAGE, self.id)
            return
        if self.random and broadcast_received == "lvl6":
            self.random = False
        if not self.random and broadcast_received == "lvl6":
            self.go_to_broadcast(int(k))
        if broadcast_received == "elevate":
            self.random = False
            if not self.choosen_ones and self.get_nb_player_on_tile() >= 6:
                self.choosen_ones = True
            
            if self.choosen_ones:
                self.share_food()
                self.drop_all()
                self.incantation()
            else:
                self.food_supply = True
