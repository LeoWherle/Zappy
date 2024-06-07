#!/usr/bin/env python3
"""
This is the main module. It contains the main function to run the application.
"""

import sys
import argparse
import json
from messages import Logger
from color import color_dic
from ai import make_new_ai

def run(args):
    """
    This function sets the log level and creates a new AI.

    Parameters:
    args (argparse.Namespace): The command line arguments.

    Returns:
    AI: The new AI.
    """
    log_level = {
            "info" : True,
            "error" : True,
            "warning" : True,
            "server" : True,
            "ai" : True
        }
    if args.nolog:
        for key in log_level:
            log_level[key] = False
    else:
        try:
            with open("ai_env.json", "r") as file:
                config = json.load(file)
                log_level = config["loglevel"]
        except Exception as _: # pylint: disable=broad-except
            print(color_dic["error"] + "Failed to load config file, using default log level" + color_dic["end"])
    logger = Logger(log_level, args.nocolor)
    return make_new_ai(args, logger)

def get_args():
    """
    This function parses the command line arguments.

    Returns:
    argparse.Namespace: The parsed command line arguments.
    """
    parser = argparse.ArgumentParser(
        description="Zappy AI"
    )

    parser.add_argument("-p", type=int, help="Port of the server", required=True)
    parser.add_argument("-n", type=str, help="Name of the team", required=True)
    parser._option_string_actions.pop("-h", None) #pylint: disable=protected-access
    parser.add_argument("-h", type=str, help="Host of the server", required=True)
    parser.add_argument("-t", help="Enable Multi threading", action='store_true')
    parser.add_argument("-nolog", help="Disable logs", action='store_true')
    parser.add_argument("-nocolor", help="Disable colored logs", action='store_true')
    parser.print_usage = parser.print_help

    if len(sys.argv) == 2 and sys.argv[1] == "-h":
        parser.print_help()
        return None

    args = parser.parse_args()

    return args

def main():
    """
    This is the main function. It gets the command line arguments and runs the application.

    Returns:
    int: The exit code.
    """
    args = get_args()

    if len(sys.argv) == 2 and sys.argv[1] == "-h":
        return 0

    if args.p >= 0:
        return run(args)

    return 84


if __name__ == "__main__":
    sys.exit(main())
