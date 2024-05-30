"""
This module contains the AI logic for the game.
"""

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
        ai_instance.fork(make_new_ai, (args, logger), threads)

    if ai_instance.is_enought_for_lvl() and ai_instance.random:
        if ai_instance.get_nb_player_on_tile() >= 6:
            ai_instance.broadcast("elevate")
        else:
            ai_instance.broadcast("lvl6")
            ai_instance.look()
            ai_instance.look()  # To delay broadcast
            ai_instance.look()

    elif ai_instance.random:
        ai_instance.move_random()

    if not ai_instance.stop:
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
    while not ai_instance.dead:
        ai_instance.net.empty_buffer(ai_instance)
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
    net.close_connection()  # End of the AI
    NB_THREAD -= 1
    for thread in threads:
        thread.join()
    return 0
