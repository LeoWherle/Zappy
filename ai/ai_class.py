from messages import logger

class AI:
    def __init__(self, team, serv):
        self.serv = serv
        self.team = team
        self.dead = False

        team_slots_left = serv.send_team(team)
        logger.info(f"Team {team} has {team_slots_left} slots left")

    # Return a dictionary of the inventory
    def inventory(self):
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
            logger.warning("AI is dead")
            return
        self.serv.send("Forward", self)
        logger.info("Moved forward")
    
    # Turn the AI right
    def turn_right(self):
        if (self.dead):
            logger.warning("AI is dead")
            return
        self.serv.send("Right", self)
        logger.info("Turned right")

    # Turn the AI left
    def turn_left(self):
        if (self.dead):
            logger.warning("AI is dead")
            return
        self.serv.send("Left", self)
        logger.info("Turned left")

    # Broadcast a message
    def broadcast(self, msg):
        if (self.dead):
            logger.warning("AI is dead")
            return
        self.serv.send(f"Broadcast {msg}", self)
        logger.info(f"Broadcasted: {msg}")

    # Fork the AI
    def fork(self):
        if (self.dead):
            logger.warning("AI is dead")
            return
        self.serv.send("Fork", self)
        logger.info("Forked")

    # Get the nb of unused slots in the team
    def get_unused_slots(self):
        if (self.dead):
            logger.warning("AI is dead")
            return
        team_slots_left = self.serv.send("Connect_nbr", self).split("\n")[0]
        logger.info(f"Team {self.team} has {team_slots_left} slots left")
        return int(team_slots_left)
    
    # Eject
    def eject(self):
        if (self.dead):
            logger.warning("AI is dead")
            return
        response = self.serv.send("Eject", self)
        if response.__contains__("ko"):
            logger.warning("Failed to eject")
            return
        logger.info("Ejected")

    # Incantation
    def incantation(self):
        if (self.dead):
            logger.warning("AI is dead")
            return
        response = self.serv.send("Incantation", self)
        if response.__contains__("ko"):
            logger.warning("Failed to incant")
            return
        logger.info("Incanted")

    # Take an object
    def take(self, obj):
        if (self.dead):
            logger.warning("AI is dead")
            return
        response = self.serv.send(f"Take {obj}", self)
        if response.__contains__("ko"):
            logger.warning(f"Failed to take {obj}")
            return
        logger.info(f"Took {obj}")

    # Drop an object
    def drop(self, obj):
        if (self.dead):
            logger.warning("AI is dead")
            return
        response = self.serv.send(f"Drop {obj}", self)
        if response.__contains__("ko"):
            logger.warning(f"Failed to drop {obj}")
            return
        logger.info(f"Dropped {obj}")

    # Look, return a list of the objects around the AI
    def look(self):
        if (self.dead):
            logger.warning("AI is dead")
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
        

