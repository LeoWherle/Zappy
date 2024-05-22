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
    def server(msg):
        print(colors.OKBLUE + "SERVER:" + colors.ENDC, msg, end="")

    @staticmethod
    def ai(msg):
        print(colors.OKCYAN + "AI:" + colors.ENDC, msg, end="")

    @staticmethod
    def info(msg):
        print(colors.OKGREEN + "INFO:" + colors.ENDC, msg)

    @staticmethod
    def error(msg):
        print(colors.FAIL + "ERROR:" + colors.ENDC, msg)

    @staticmethod
    def warning(msg):
        print(colors.WARNING + "WARNING:" + colors.ENDC, msg)