from connection import ServerConnection
from ai_class import AI
import threading

nb_thread = 0 # (temporary) Global variable to limit the number of AI on map

# Change the function to change the AI logic
def make_ai_actions(ai, threads, args, logger):
    global nb_thread # (temporary) Global variable to limit the number of AI on map

    if (ai.get_unused_slots() > 0 and nb_thread < 9):
        nb_thread += 1
        ai.fork(make_new_ai, (args, logger, ai.id + 1), threads)

    if (ai.is_enought_for_lvl() and ai.random):
        if (ai.get_nb_player_on_tile() >= 6):
            ai.broadcast("elevate")
        else:
            ai.broadcast("lvl6")
            ai.look()
            ai.look() # To delay broadcast
            ai.look()

    elif(ai.random):
        ai.move_random()

    if (not ai.stop):
        ai.take_all()
    else:
        ai.share_food()

    if (ai.food_supply):
        if ai.get_nb_player_on_tile() >= 6:
            ai.drop_all_food()
        else:
            ai.take_all_food()
            ai.move_random()
    

def start_ai_logic(ai, threads, args, logger):
    while (not ai.dead):
        ai.net.empty_buffer(ai)
        if (ai.is_elevating):
            continue
        
        make_ai_actions(ai, threads, args, logger)
        
        ai.net.send_buffer(ai)

def make_new_ai(args, logger, id):
    global nb_thread # (temporary) Global variable to limit the number of AI on map

    threads = []
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
