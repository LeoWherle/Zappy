#!/usr/bin/env python3
from sys import argv
import argparse
from connection import send_to_server, connect_to_server, close_connection

def run(args):
    """Run the program"""
    sock = connect_to_server(args.h, args.p)
    if not sock:
        return 84
    send_to_server(sock, "ping\n")
    close_connection(sock)
    return 0


def get_args():
    parser = argparse.ArgumentParser(
        description="Zappy AI"
    )

    parser.add_argument("-p", type=int, help="Port of the server", required=True)
    parser.add_argument("-n", type=str, help="Name of the team", required=True)
    parser._option_string_actions.pop("-h", None)
    parser.add_argument("-h", type=str, help="Host of the server", required=True)

    if len(argv) == 2 and argv[1] == "-h":
        parser.print_help()
        return None
        
    args = parser.parse_args()

    return args
    

def main():
    args = get_args()

    if args is None:
        return 0

    if args.p >= 0:
        return run(args)

    return 84


if __name__ == "__main__":
    exit(main())