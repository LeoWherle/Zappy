##
## EPITECH PROJECT, 2024
## B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
## File description:
## Makefile
##

GRAY		=	\033[1;30m
RED			=	\033[1;31m
GREEN 		= 	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

RESET		=	\033[0m

BIN_AI=zappy_ai
BIN_SERVER=zappy_server
BIN_GUI=zappy_gui

FOLDER_AI=ai
FOLDER_SERVER=server
FOLDER_GUI=gui


MAKE  = make --no-print-directory

RAYLIB_PATH=gui/raylib/src
RAYLIB_CPP_PATH=gui/raylib-cpp

RULE =
# used with make DEBUG=n
ifeq ($(DEBUG), n)
	RULE = "DEBUG=n"
else ifeq ($(DEBUG), y)
	RULE = "DEBUG=y"
endif

all: $(BIN_SERVER) $(BIN_AI)  $(BIN_GUI)

submodules:
	@git submodule update --init --recursive

install: submodules setup

install-raylib:
	$(MAKE) -C $(RAYLIB_PATH) clean
	$(MAKE) -C $(RAYLIB_PATH) PLATFORM=PLATFORM_DESKTOP

install-raylib-cpp-example:
	@rm -rf $(RAYLIB_CPP_PATH)/build
	@mkdir $(RAYLIB_CPP_PATH)/build
	@cmake -B$(RAYLIB_CPP_PATH)/build -S$(RAYLIB_CPP_PATH)
	$(MAKE) -C $(RAYLIB_CPP_PATH)/build

setup: install-raylib
	$(MAKE) -C $(FOLDER_GUI) setup
	@echo -e "$(GREEN)✓ Raylib installed sucessfully$(RESET)"

$(BIN_AI):
	ln -s -f $(FOLDER_AI)/main.py $(BIN_AI)

$(BIN_SERVER):
	@$(MAKE) -C $(FOLDER_SERVER)
	cp $(FOLDER_SERVER)/$(BIN_SERVER) .

$(BIN_GUI):
	@$(MAKE) -C $(FOLDER_GUI)
	cp $(FOLDER_GUI)/$(BIN_GUI) .

build_lib:
	@$(MAKE) -C $(FOLDER_GUI) setup

clean:
	@$(MAKE) -C $(FOLDER_SERVER) clean
	@$(MAKE) -C $(FOLDER_GUI) clean

fclean:
	rm -f $(BIN_AI)
	@$(MAKE) -C $(FOLDER_SERVER) fclean
	rm -f $(BIN_SERVER)
	@$(MAKE) -C $(FOLDER_GUI) fclean
	rm -f $(BIN_GUI)

re: fclean all

.PHONY: all zappy_ai zappy_server zappy_gui clean fclean re setup \
install-raylib install-raylib-cpp install build_lib submodules
.NOTPARALLEL: re install
