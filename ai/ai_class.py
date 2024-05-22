from messages import logger

class AI:
    def __init__(self, team, serv):
        self.serv = serv
        self.team = team

        team_slots_left = serv.send_team(team)
        logger.info(f"Team {team} has {team_slots_left} slots left")

    # Return a dictionary of the inventory
    def inventory(self):
        list = self.serv.send("Inventory").split("[")[1].split(",")
        dic = {}
        for elem in list:
            key = elem.split(" ")[1]
            value = int(elem.split(" ")[2])
            dic[key] = value
        return dic
    
    # Move the AI forward
    def forward(self):
        self.serv.send("Forward")
        logger.info("Moved forward")
    
    # Turn the AI right
    def turn_right(self):
        self.serv.send("Right")
        logger.info("Turned right")

    # Turn the AI left
    def turn_left(self):
        self.serv.send("Left")
        logger.info("Turned left")

    # Broadcast a message
    def broadcast(self, msg):
        self.serv.send(f"Broadcast {msg}")
        logger.info(f"Broadcasted: {msg}")

    # Fork the AI
    def fork(self):
        self.serv.send("Fork")
        logger.info("Forked")

    # Get the nb of unused slots in the team
    def get_unused_slots(self):
        team_slots_left = self.serv.send("Connect_nbr").split("\n")[0]
        logger.info(f"Team {self.team} has {team_slots_left} slots left")
        return int(team_slots_left)

