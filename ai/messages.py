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

def server_print(msg):
    print(colors.OKBLUE + "SERVER:" + colors.ENDC, msg)

def info_print(msg):
    print(colors.OKGREEN + "INFO:" + colors.ENDC, msg)

def error_print(msg):
    print(colors.FAIL + "ERROR:" + colors.ENDC, msg)

def warning_print(msg):
    print(colors.WARNING + "WARNING:" + colors.ENDC, msg)