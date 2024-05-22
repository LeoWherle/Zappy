from messages import logger
from connection import Server

class AI:
    def __init__(self, team, serv):
        self.serv = serv
        self.team = team
        self.team_slots_left = serv.send_team(team)
        logger.info(f"Team {team} has {self.team_slots_left} slots left")

    # Return a dictionary of the inventory
    def inventory(self):
        list = self.serv.send("Inventory").split("[")[1].split(",")
        dic = {}
        for elem in list:
            key = elem.split(" ")[1]
            value = int(elem.split(" ")[2])
            dic[key] = value
        return dic

