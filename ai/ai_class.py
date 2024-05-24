class AI:
    def __init__(self, team, net, id=0):
        self.net = net
        self.team = team
        self.lvl = 1
        self.id = id
        self.dead = False
        self.last_eject = None
        self.broadcast_received = []

        team_slots_left = net.send_team(team)
        if (team_slots_left == -1):
            self.dead = True
            return
        self.net.logger.info(f"Team {team} has {team_slots_left} slots left", self.id)

    # Return a dictionary of the inventory
    def inventory(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        list = self.net.send("Inventory", self).split("[")[1].split(",")
        dic = {}
        for elem in list:
            key = elem.split(" ")[1]
            value = int(elem.split(" ")[2])
            dic[key] = value
        return dic
    
    # Move the AI forward
    def forward(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.send("Forward", self)
        self.net.logger.info("Moved forward", self.id)
    
    # Turn the AI right
    def turn_right(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.send("Right", self)
        self.net.logger.info("Turned right", self.id)

    # Turn the AI left
    def turn_left(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.send("Left", self)
        self.net.logger.info("Turned left", self.id)

    # Broadcast a message
    def broadcast(self, msg):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.send(f"Broadcast {msg}", self)
        self.net.logger.info(f"Broadcasted: {msg}", self.id)

    # Fork the AI
    def fork(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        self.net.send("Fork", self)
        self.net.logger.info("Forked", self.id)

    # Get the nb of unused slots in the team
    def get_unused_slots(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        team_slots_left = self.net.send("Connect_nbr", self).split("\n")[0]
        self.net.logger.info(f"Team {self.team} has {team_slots_left} slots left", self.id)
        try:
            team_slots_left = int(team_slots_left)
        except:
            team_slots_left = 0
        return team_slots_left
    
    # Eject
    def eject(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        response = self.net.send("Eject", self)
        if response.__contains__("ko"):
            self.net.logger.warning("Failed to eject", self.id)
            return
        self.net.logger.info("Ejection worked", self.id)

    # Incantation
    def incantation(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        response = self.net.send("Incantation", self)
        if response.__contains__("ko"):
            self.net.logger.warning("Failed to incant", self.id)
            return
        self.net.logger.info("Incanted", self.id)

    # Take an object
    def take(self, obj):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        response = self.net.send(f"Take {obj}", self)
        if response.__contains__("ko"):
            self.net.logger.warning(f"Failed to take {obj}", self.id)
            return
        self.net.logger.info(f"Took {obj}", self.id)
    
    # Take all objects on a tile
    def take_all(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        list = self.look()
        if list == None:
            return
        try:
            list = list[0]
            for elem in list:
                if elem != "player":
                    self.take(elem)
        except:
            return

    # Drop an object
    def drop(self, obj):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        response = self.net.send(f"Drop {obj}", self)
        if response.__contains__("ko"):
            self.net.logger.warning(f"Failed to drop {obj}", self.id)
            return
        self.net.logger.info(f"Dropped {obj}", self.id)

    # Look, return a list of the objects around the AI
    def look(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return None
        response = self.net.send("Look", self)
        try:
            list = response.split("[")[1].split(",")
            for i in range(len(list)):
                list[i] = list[i].split(" ")
            for elem in list:
                for i in range(len(elem) - 1):
                    if elem[i] == "":
                        elem.pop(i)
            list.pop(-1)
        except:
            list = []
        return list
        
    def handle_broadcast(self):
        if (self.dead):
            self.net.logger.warning("AI is dead", self.id)
            return
        for elem in self.broadcast_received:
            if elem[1] == "GoGoGadgetIncanto":  # Example of broadcast usage
                self.incantation()
        self.broadcast_received = []

