class colors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class Logger:
    def __init__(self, log_level):
        self.log_level = log_level
        if self.log_level is None:
            self.log_level = {
                "info" : True,
                "error" : True,
                "warning" : True,
                "server" : True,
                "ai" : True
            }

    def server(self, msg, id):
        if not self.log_level["server"]:
            return
        print(colors.OKBLUE + f"SERVER for AI {id}:" + colors.ENDC, msg, end="")

    def ai(self, msg, id):
        if not self.log_level["ai"]:
            return
        print(colors.OKCYAN + f"AI {id}:" + colors.ENDC, msg, end="")

    def info(self, msg, id):
        if not self.log_level["info"]:
            return
        print(colors.OKGREEN + f"INFO AI {id}:" + colors.ENDC, msg)

    def error(self, msg, id):
        if not self.log_level["error"]:
            return
        print(colors.FAIL + f"ERROR AI {id}:" + colors.ENDC, msg)

    def warning(self, msg, id):
        if not self.log_level["warning"]:
            return
        print(colors.WARNING + f"WARNING AI {id}:" + colors.ENDC, msg)