from connection import ServerConnection
from ai_class import AI
import threading

nb_thread = 0 # (temporary) Global variable to limit the number of AI on map

# Change the function to change the AI logic
def make_ai_actions(ai, threads, args, logger):
    global nb_thread # (temporary) Global variable to limit the number of AI on map
    if (ai.get_unused_slots() > 0 and nb_thread < 5):
        nb_thread += 1
        ai.fork(make_new_ai, (args, logger, ai.id + 1), threads)

    if (ai.incantation()):
        ai.move_random()
    if (ai.get_nb_player_on_tile() == 1):
        ai.take_all()
        ai.move_random()
    else:
        ai.drop_all()


def start_ai_logic(ai, threads, args, logger):
    while (not ai.dead):
        ai.net.empty_buffer(ai)
        if (ai.is_elevating):
            continue
        
        make_ai_actions(ai, threads, args, logger)
        
        ai.net.send_buffer(ai)

def make_new_ai(args, logger, id):
    threads = []
    global nb_thread # (temporary) Global variable to limit the number of AI on map
    net = ServerConnection(logger, args.h, args.p) # AI Connection to Server
    if not net.connect():
        return 84
    net.multi_threading = args.t

    ai = AI(args.n, net, id) # AI Creation
    start_ai_logic(ai, threads, args, logger) # AI Logic
    net.close_connection() # End of the AI
    nb_thread -= 1
    for thread in threads:
        thread.join()
    return 0
