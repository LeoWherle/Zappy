##
## EPITECH PROJECT, 2023
## Makefile
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

BUILD_DIR = build/

MAKE  = make --no-print-directory
CC = gcc

RULE =
# used with make DEBUG=n
ifeq ($(DEBUG), n)
	CFLAGS += -O2
	RULE = "DEBUG=n"
	BUILD_PATH := $(BUILD_DIR)release/
# used with make DEBUG=y
else ifeq ($(DEBUG), y)
	LDFLAGS += -fsanitize=address -fsanitize-address-use-after-scope
	CFLAGS += -g3 -DDEBUG  -fsanitize=address
	RULE = "DEBUG=y"
	BUILD_PATH := $(BUILD_DIR)asan/
else
	CFLAGS += -g
	BUILD_PATH := $(BUILD_DIR)debug/
endif

SRC_SERV = $(shell find app/src/ -name "*.c" -type f)
OBJ_SERV = 	$(SRC_SERV:%.c=$(BUILD_PATH)%.o)
DEPS_SERV = 	$(OBJ_SERV:%.o=%.d)

LIBINC = $(addsuffix /include, $(addprefix -I, $(LIBS)))
LIB_FLAGS = -L$(BUILD_PATH) $(addprefix -l, $(LIBS))

CFLAGS += -W -Wall -Wextra $(LIBINC)

CFLAGS += -Iapp/include
CFLAGS += -std=gnu2x

LDFLAGS += $(LIB_FLAGS)
CRITFLAGS = -lcriterion --coverage


$(BUILD_PATH)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


all: app

$(BUILD_PATH)$(BIN): lib_build $(OBJ_SERV)
	$(CC) -o $(BUILD_PATH)$(BIN) $(OBJ_SERV) $(LDFLAGS)
	@echo -e "$(GREEN)✓ Compiled $(BIN)$(RESET)"

app: $(BUILD_PATH)$(BIN)
	cp $(BUILD_PATH)$(BIN) $(BIN)

lib_build:
	@for i in $(LIBS); do $(MAKE) -C $$i $(RULE); done

clean:
	@rm -rf $(BUILD_DIR)asan $(BUILD_DIR)debug $(BUILD_DIR)release
	@for j in "DEBUG=n" "DEBUG=y" ""; do \
	for i in $(LIBS); do $(MAKE) -C $$i clean $$j; done \
	done

fclean: clean
	@for j in "DEBUG=n" "DEBUG=y" ""; do \
	for i in $(LIBS); do $(MAKE) -C $$i fclean $$j; done \
	done
	@rm -f unit-tests
	@rm -f $(BIN)
	@rm -f $(BUILD_DIR)asan/$(BIN)
	@rm -f $(BUILD_DIR)debug/$(BIN)
	@rm -f $(BUILD_DIR)release/$(BIN)

re: fclean all

tests_run:
	@for i in $(LIBS); do $(MAKE) -C $$i tests_run; done

.PHONY: all clean fclean re debug tests_run lib_build server
.NOTPARALLEL: re
