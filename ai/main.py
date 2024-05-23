#!/usr/bin/env python3
from sys import argv
import argparse
from connection import ServerConnection
from ai_class import AI

def run(args):
    """Run the program"""

    serv = ServerConnection(args.h, args.p)
    if not serv.connect():
        return 84

    ai = AI(args.n, serv, 0)
    while (not ai.dead and ai.lvl < 2):
        ai.incantation()
        ai.take("food")
        ai.forward()

    ai.inventory()

    input("Press Enter to disconnect... ")

    serv.close_connection() # End of the program
    return 0


def get_args():
    parser = argparse.ArgumentParser(
        description="Zappy AI"
    )

    parser.add_argument("-p", type=int, help="Port of the server", required=True)
    parser.add_argument("-n", type=str, help="Name of the team", required=True)
    parser._option_string_actions.pop("-h", None)
    parser.add_argument("-h", type=str, help="Host of the server", required=True)
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