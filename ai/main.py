#!/usr/bin/env python3
from sys import argv
import argparse
from connection import ServerConnection
from ai_class import AI
import threading
from messages import Logger


def new_ai(args, logger, id):
    threads = []
    net = ServerConnection(logger, args.h, args.p)
    if not net.connect():
        return 84

    ai = AI(args.n, net, id)
    while (not ai.dead):
        if (ai.get_unused_slots() > 0):
            ai.fork()
            threads.append(threading.Thread(target=new_ai, args=(args, logger, id + 1)))
            threads[-1].start()
        ai.handle_broadcast()
        ai.take("food")
        ai.forward()
        ai.broadcast("GoGoGadgetIncanto")

    net.close_connection() # End of the program
    for thread in threads:
        thread.join()
    return 0

def run(args):
    log_level = {
        "info" : True,
        "error" : True,
        "warning" : True,
        "server" : True,
        "ai" : True
    }
    logger = Logger(log_level)
    return new_ai(args, logger, 0)

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