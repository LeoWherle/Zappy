#!/usr/bin/env python3
from sys import argv
import argparse
from messages import Logger
from ai import make_new_ai

def run(args):
    log_level = {
        "info" : True,
        "error" : True,
        "warning" : True,
        "server" : True,
        "ai" : True
    }
    if args.nolog:
        for key in log_level.keys():
            log_level[key] = False
    logger = Logger(log_level)
    return make_new_ai(args, logger, 0)

def get_args():
    parser = argparse.ArgumentParser(
        description="Zappy AI"
    )

    parser.add_argument("-p", type=int, help="Port of the server", required=True)
    parser.add_argument("-n", type=str, help="Name of the team", required=True)
    parser._option_string_actions.pop("-h", None)
    parser.add_argument("-h", type=str, help="Host of the server", required=True)
    parser.add_argument("-t", help="Enable Multi threading", action='store_true')
    parser.add_argument("-nolog", help="Disable logs", action='store_true')
    parser.print_usage = parser.print_help

    if len(argv) == 2 and argv[1] == "-h":
        parser.print_help()
        return None
        
    args = parser.parse_args()

    return args
    

def main():
    args = get_args()

    if len(argv) == 2 and argv[1] == "-h":
        return 0

    if args.p >= 0:
        return run(args)

    return 84


if __name__ == "__main__":
    exit(main())