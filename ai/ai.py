"""
This module contains the AI logic for the game.
"""

import threading
from connection import ServerConnection
from ai_class import AI

NB_THREAD = 0  # (Temporary) Global variable to limit the number of AI on map


def make_ai_actions(ai_instance, threads, args, logger):
    """
    This function defines the actions of the AI.

    Parameters:
    ai_instance (AI): The AI instance.
    threads (list): The list of threads.
    args (argparse.Namespace): The command line arguments.
    logger (Logger): The logger.
    """
    global NB_THREAD # (Temporary) Global variable to limit the number of AI on map pylint: disable=global-statement

    if ai_instance.get_unused_slots() > 0 and NB_THREAD < 9:
        NB_THREAD += 1
        if (not ai_instance.net.multi_threading):
            ai_instance.net.logger.info("Mutli threading is disabled, manually connect an AI", ai_instance.id)
        else:
            threads.append(threading.Thread(target=make_new_ai, args=(args, logger)))
            threads[-1].start()
    elif (NB_THREAD < 9):
        ai_instance.fork()

    if not ai_instance.king and ai_instance.random and ai_instance.is_enought_for_lvl():
        ai_instance.king = True

    if ai_instance.king:
        if ai_instance.get_nb_player_on_tile() >= 6:
            ai_instance.broadcast("elevate")
            ai_instance.share_food()
            ai_instance.drop_all()
        else:
            ai_instance.broadcast("lvl6")
            ai_instance.look()
            ai_instance.look()  # To delay broadcast
            ai_instance.look()

    elif ai_instance.random:
        ai_instance.move_random()

    if not ai_instance.choosen_ones and not ai_instance.king:
        ai_instance.take_all()


def start_ai_logic(ai_instance, threads, args, logger):
    """
    This function starts the AI logic.

    Parameters:
    ai_instance (AI): The AI instance.
    threads (list): The list of threads.
    args (argparse.Namespace): The command line arguments.
    logger (Logger): The logger.
    """
    while not ai_instance.dead and ai_instance.lvl < 8:
        ai_instance.net.empty_buffer(ai_instance)
        if ai_instance.dead:
            break
        if ai_instance.is_elevating:
            continue

        make_ai_actions(ai_instance, threads, args, logger)

        ai_instance.net.send_buffer(ai_instance)


def make_new_ai(args, logger):
    """
    This function creates a new AI.

    Parameters:
    args (argparse.Namespace): The command line arguments.
    logger (Logger): The logger.
    ai_id (int): The ID of the AI.

    Returns:
    int: The exit code.
    """
    global NB_THREAD # (Temporary) Global variable to limit the number of AI on map pylint: disable=global-statement

    threads = []
    net = ServerConnection(logger, args.h, args.p)  # AI Connection to Server
    if not net.connect():
        return 84
    net.multi_threading = args.t

    ai_instance = AI(args.n, net)  # AI Creation
    start_ai_logic(ai_instance, threads, args, logger)  # AI Logic
    net.close_connection(ai_instance)  # End of the AI
    NB_THREAD -= 1
    for thread in threads:
        thread.join()
    return 0
