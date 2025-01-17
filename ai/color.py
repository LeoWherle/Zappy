"""
This module defines colors for the terminal output.
"""

HEADER = '\033[95m'
OKBLUE = '\033[94m'
OKCYAN = '\033[96m'
OKGREEN = '\033[92m'
WARNING = '\033[93m'
FAIL = '\033[91m'
ENDC = '\033[0m'
BOLD = '\033[1m'
UNDERLINE = '\033[4m'

color_dic: dict = {"info": OKGREEN,
            "error": FAIL,
            "warning": WARNING,
            "server": OKBLUE,
            "ai": OKCYAN,
            "end": ENDC,
            "bold": BOLD,
            "underline": UNDERLINE}
