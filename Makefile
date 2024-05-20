##
## EPITECH PROJECT, 2024
## B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
## File description:
## Makefile
##


all: zappy_ai zappy_server zappy_gui

zappy_ai:
	@$(MAKE) -C zappy_ai/

zappy_server:
	@$(MAKE) -C zappy_server/

zappy_gui:
	@$(MAKE) -C zappy_gui/

clean:
	@$(MAKE) -C zappy_ai/ clean
	@$(MAKE) -C zappy_server/ clean
	@$(MAKE) -C zappy_gui/ clean

fclean:
	@$(MAKE) -C zappy_ai/ fclean
	@$(MAKE) -C zappy_server/ fclean
	@$(MAKE) -C zappy_gui/ fclean

re: fclean all

.PHONY: all zappy_ai zappy_server zappy_gui clean fclean re
