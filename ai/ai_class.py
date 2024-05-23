from messages import logger

class AI:
    def __init__(self, team, serv, id=0):
        self.serv = serv
        self.team = team
        self.lvl = 1
        self.id = id
        self.dead = False

        team_slots_left = serv.send_team(team)
        logger.info(f"Team {team} has {team_slots_left} slots left", self.id)

    # Return a dictionary of the inventory
    def inventory(self):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        list = self.serv.send("Inventory", self).split("[")[1].split(",")
        dic = {}
        for elem in list:
            key = elem.split(" ")[1]
            value = int(elem.split(" ")[2])
            dic[key] = value
        return dic
    
    # Move the AI forward
    def forward(self):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        self.serv.send("Forward", self)
        logger.info("Moved forward", self.id)
    
    # Turn the AI right
    def turn_right(self):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        self.serv.send("Right", self)
        logger.info("Turned right", self.id)

    # Turn the AI left
    def turn_left(self):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        self.serv.send("Left", self)
        logger.info("Turned left", self.id)

    # Broadcast a message
    def broadcast(self, msg):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        self.serv.send(f"Broadcast {msg}", self)
        logger.info(f"Broadcasted: {msg}", self.id)

    # Fork the AI
    def fork(self):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        self.serv.send("Fork", self)
        logger.info("Forked", self.id)

    # Get the nb of unused slots in the team
    def get_unused_slots(self):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        team_slots_left = self.serv.send("Connect_nbr", self).split("\n")[0]
        logger.info(f"Team {self.team} has {team_slots_left} slots left", self.id)
        return int(team_slots_left)
    
    # Eject
    def eject(self):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        response = self.serv.send("Eject", self)
        if response.__contains__("ko"):
            logger.warning("Failed to eject", self.id)
            return
        logger.info("Ejected", self.id)

    # Incantation
    def incantation(self):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        response = self.serv.send("Incantation", self)
        if response.__contains__("ko"):
            logger.warning("Failed to incant", self.id)
            return
        logger.info("Incanted", self.id)

    # Take an object
    def take(self, obj):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        response = self.serv.send(f"Take {obj}", self)
        if response.__contains__("ko"):
            logger.warning(f"Failed to take {obj}", self.id)
            return
        logger.info(f"Took {obj}", self.id)

    # Drop an object
    def drop(self, obj):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        response = self.serv.send(f"Drop {obj}", self)
        if response.__contains__("ko"):
            logger.warning(f"Failed to drop {obj}", self.id)
            return
        logger.info(f"Dropped {obj}", self.id)

    # Look, return a list of the objects around the AI
    def look(self):
        if (self.dead):
            logger.warning("AI is dead", self.id)
            return
        response = self.serv.send("Look", self)
        list = response.split("[")[1].split(",")
        for i in range(len(list)):
            list[i] = list[i].split(" ")
        for elem in list:
            for i in range(len(elem) - 1):
                if elem[i] == "":
                    elem.pop(i)
        
        list.pop(-1)
        return list
        

