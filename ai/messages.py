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

class logger:

    @staticmethod
    def server(msg, id):
        print(colors.OKBLUE + f"SERVER for AI {id}:" + colors.ENDC, msg, end="")

    @staticmethod
    def ai(msg, id):
        print(colors.OKCYAN + f"AI {id}:" + colors.ENDC, msg, end="")

    @staticmethod
    def info(msg, id):
        print(colors.OKGREEN + f"INFO AI {id}:" + colors.ENDC, msg)

    @staticmethod
    def error(msg, id):
        print(colors.FAIL + f"ERROR AI {id}:" + colors.ENDC, msg)

    @staticmethod
    def warning(msg, id):
        print(colors.WARNING + f"WARNING AI {id}:" + colors.ENDC, msg)