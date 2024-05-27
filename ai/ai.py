from connection import ServerConnection
from ai_class import AI
from random import randint
import threading

# Temporary function
def move_random(ai):
    random = randint(0, 3)
    match random:
        case 0:
            ai.forward()
        case 1:
            ai.turn_right()
            ai.forward()
        case 2:
            ai.turn_left()
            ai.forward()

# Change the function to change the AI logic
def make_ai_actions(ai, threads, args, logger):
    if (ai.get_unused_slots() > 0):
        ai.fork(make_new_ai, (args, logger, ai.id + 1), threads)

    ai.incantation()
    ai.take("food")
    move_random(ai)


def start_ai_logic(ai, threads, args, logger):
    while (not ai.dead):
        if (ai.is_elevating):
            ai.net.empty_buffer(ai)
            continue
        
        make_ai_actions(ai, threads, args, logger)
        
        ai.net.send_buffer(ai)
        ai.net.empty_buffer(ai)

def make_new_ai(args, logger, id):
    threads = []
    net = ServerConnection(logger, args.h, args.p) # AI Connection to Server
    if not net.connect():
        return 84
    net.multi_threading = args.t

    ai = AI(args.n, net, id) # AI Creation
    start_ai_logic(ai, threads, args, logger) # AI Logic
    net.close_connection() # End of the AI
    for thread in threads:
        thread.join()
    return 0
