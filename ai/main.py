#!/usr/bin/env python3
from sys import argv
import argparse
from connection import Server
from ai_class import AI

def run(args):
    """Run the program"""

    serv = Server(args.h, args.p)
    if not serv.connect():
        return 84

    ai = AI(args.n, serv)
    ai.inventory() # Get the inventory as a dictionary

    input("\nPress Enter to exit... (fake AI loop)") # fake AI loop

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