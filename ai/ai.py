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
def start_ai_logic(ai, threads, args, logger):
    while (not ai.dead):
        if (ai.get_unused_slots() > 0):
            ai.fork(make_new_ai, (args, logger, ai.id + 1), threads)

        ai.handle_broadcast()
        if (ai.lvl == 1):
            ai.take("food")
            if (ai.get_nb_player_on_tile() == 1):
                ai.incantation()
            move_random(ai)
        else:
            if (ai.get_nb_player_on_tile() == 1):
                ai.take("food")
                ai.take("deraumere")
                ai.take("sibur")
                ai.take("phiras")
                move_random(ai)
            else:
                ai.take("food")
                ai.drop_all()
                ai.incantation()

def make_new_ai(args, logger, id):
    threads = []
    net = ServerConnection(logger, args.h, args.p) # AI Connection to Server
    if not net.connect():
        return 84

    ai = AI(args.n, net, id) # AI Creation
    start_ai_logic(ai, threads, args, logger) # AI Logic
    net.close_connection() # End of the AI
    for thread in threads:
        thread.join()
    return 0