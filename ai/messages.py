"""
This module defines a Logger class for handling different types of log messages
with various log levels.
"""

from color import *

NEEDED_KEYS = ["info", "error", "warning", "server", "ai"]

class Logger:
    """
    Logger class for handling different types of log messages with various log levels.
    """
    def __init__(self, log_level):
        """
        Initialize the Logger with a specific log level.

        Parameters:
        log_level (dict): A dictionary specifying the log levels.
        """
        self.log_level = log_level
        if self.log_level is None:
            self.log_level = {
                "info" : True,
                "error" : True,
                "warning" : True,
                "server" : True,
                "ai" : True
            }
        for elem in NEEDED_KEYS:
            if self.log_level[elem] is None:
                self.log_level[elem] = True

        print(BOLD + "=============================================")
        print(UNDERLINE + "Log level:" + ENDC)
        for key in self.log_level:
            if self.log_level[key]:
                print(BOLD + OKGREEN + f"{key} is enabled" + ENDC)
            else:
                print(BOLD + FAIL + f"{key} is disabled" + ENDC)
        print(BOLD + "=============================================" + ENDC)

    def server_log(self, msg, ai_id):
        """
        Log a server message if the server log level is enabled.

        Parameters:
        msg (str): The message to log.
        ai_id (str): The ID of the AI.
        """
        if not self.log_level["server"] or msg == "":
            return
        print(OKBLUE + f"SERVER for AI {ai_id}:" + ENDC, msg, end="")

    def ai_log(self, msg, ai_id):
        """
        Log an AI message if the AI log level is enabled.

        Parameters:
        msg (str): The message to log.
        ai_id (str): The ID of the AI.
        """
        if not self.log_level["ai"] or msg == "":
            return
        print(OKCYAN + f"AI {ai_id}:" + ENDC, msg, end="")

    def info(self, msg, ai_id):
        """
        Log an info message if the info log level is enabled.

        Parameters:
        msg (str): The message to log.
        ai_id (str): The ID of the AI.
        """
        if not self.log_level["info"] or msg == "":
            return
        print(OKGREEN + f"INFO AI {ai_id}:" + ENDC, msg)

    def error(self, msg, ai_id):
        """
        Log an error message if the error log level is enabled.

        Parameters:
        msg (str): The message to log.
        ai_id (str): The ID of the AI.
        """
        if not self.log_level["error"] or msg == "":
            return
        print(FAIL + f"ERROR AI {ai_id}:" + ENDC, msg)

    def warning(self, msg, ai_id):
        """
        Log a warning message if the warning log level is enabled.

        Parameters:
        msg (str): The message to log.
        ai_id (str): The ID of the AI.
        """
        if not self.log_level["warning"] or msg == "":
            return
        print(WARNING + f"WARNING AI {ai_id}:" + ENDC, msg)
