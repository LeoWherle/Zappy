##
## EPITECH PROJECT, 2024
## B-YEP-400-TLS-4-1-zappy-leo.wehrle [WSL: Ubuntu]
## File description:
## Makefile
##

include config.mk

BEGINL		= 	\033[A
CLEARL		= 	\033[2K
COL_END		= 	\033[0m
CLEAR_COL	=	\033[2K\033[A
GRAY		=	\033[1;30m
RED			=	\033[1;31m
GREEN 		= 	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

RESET		=	\033[0m

MAKE  = make --no-print-directory
CC = g++

RULE =
# used with make DEBUG=n
ifeq ($(DEBUG), n)
	CFLAGS += -O2
	RULE = "DEBUG=n"
# used with make DEBUG=y
else ifeq ($(DEBUG), y)
	LDFLAGS += -fsanitize=address -fsanitize-address-use-after-scope
	CFLAGS += -g3 -DDEBUG  -fsanitize=address
	RULE = "DEBUG=y"
else
	CFLAGS += -g
endif

SRC_GUI = $(shell find src/ -name "*.cpp" -type f)
OBJ_GUI = 	$(SRC_GUI:%.c=$(BUILD_PATH)%.o)
DEPS_GUI = 	$(OBJ_GUI:%.o=%.d)

#LIBINC = $(addsuffix /include, $(addprefix -I, $(LIBS)))
#LIB_FLAGS = -L$(BUILD_PATH) $(addprefix -l, $(LIBS))
RAYLIB_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

CFLAGS += -W -Wall -Wextra

CFLAGS += -Iraylib/include

LDFLAGS += $(RAYLIB_FLAGS)
CRITFLAGS = -lcriterion --coverage


%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


all: $(BIN)

$(BIN): lib_build $(OBJ_GUI)
	$(CC) -o $(BIN) $(OBJ_GUI) $(LDFLAGS)
	@echo -e "$(GREEN)✓ Compiled $(BIN)$(RESET)"

#lib_build:
#	@for i in $(LIBS); do $(MAKE) -C $$i $(RULE); done

clean:
#	@for j in "DEBUG=n" "DEBUG=y" ""; do \
	for i in $(LIBS); do $(MAKE) -C $$i clean $$j; done \
	done

fclean: clean
#	@for j in "DEBUG=n" "DEBUG=y" ""; do \
	for i in $(LIBS); do $(MAKE) -C $$i fclean $$j; done \
	done
	@$(MAKE) -C 
	@rm -f unit-tests
	@rm -f $(BIN)

re: fclean all

#tests_run:
#	@for i in $(LIBS); do $(MAKE) -C $$i tests_run; done

.PHONY: all clean fclean re debug tests_run lib_build
.NOTPARALLEL: re
