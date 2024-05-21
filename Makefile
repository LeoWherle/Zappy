##
## EPITECH PROJECT, 2024
## B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
## File description:
## Makefile
##

BIN_AI=zappy_ai
BIN_SERVER=zappy_server
BIN_GUI=zappy_gui

FOLDER_AI=ai/
FOLDER_SERVER=server/
FOLDER_GUI=gui/


MAKE  = make --no-print-directory


all: $(BIN_SERVER) $(BIN_AI)  $(BIN_GUI)

$(BIN_AI):
	@$(MAKE) -C $(FOLDER_AI)
	mv $(FOLDER_AI)$(BIN_AI) .

$(BIN_SERVER):
	@$(MAKE) -C $(FOLDER_SERVER)
	mv $(FOLDER_SERVER)$(BIN_SERVER) .

$(BIN_GUI):
	@$(MAKE) -C $(FOLDER_GUI)
	mv $(FOLDER_GUI)$(BIN_GUI) .

clean:
	@$(MAKE) -C $(FOLDER_AI) clean
	@$(MAKE) -C $(FOLDER_SERVER) clean
	@$(MAKE) -C $(FOLDER_GUI) clean

fclean:
	@$(MAKE) -C $(FOLDER_AI) fclean
	@$(MAKE) -C $(FOLDER_SERVER) fclean
	@$(MAKE) -C $(FOLDER_GUI) fclean

re: fclean all

.PHONY: all zappy_ai zappy_server zappy_gui clean fclean re
.NOTPARALLEL: re