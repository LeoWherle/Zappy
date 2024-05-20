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
GRAY		=	\033[1;30m
RED			=	\033[1;31m
GREEN 		= 	\033[1;32m
YELLOW		=	\033[1;33m
BLUE		=	\033[1;34m
PURPLE		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m

RESET		=	\033[0m

BUILD_DIR = ../build/
CC = gcc

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

SRC 	=	$(shell find src/ -name "*.c" -type f)

CRIT_LIST	=	$(shell find ../tests/lib/$(NAME)/ -name "*.c" -type f)

SRC_CRIT = $(SRC)
TEST_CRIT = $(CRIT_LIST)

OBJ = 	$(SRC:%.c=$(BUILD_PATH)$(NAME)/%.o)
OBJ_CRIT = $(CRIT_LIST:%.c=$(BUILD_PATH)$(NAME)/%.o)
OBJ_SRC_CRIT = $(SRC:%.c=$(BUILD_PATH)tests/$(NAME)/%.o)
DEPS = 	$(OBJ:%.o=%.d)

CFLAGS = -W -Wall -Wextra -Iinclude
CRITFLAGS = -lcriterion --coverage

$(BUILD_DIR)tests/$(NAME)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -c -o $@

$(BUILD_PATH)$(NAME)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $^ -c -o $@

$(BUILD_PATH)$(LIBNAME): $(OBJ)
	ar rc $(BUILD_PATH)$(LIBNAME) $(OBJ)
	@echo -e "$(GREEN)✓ Compiled $(LIBNAME)$(RESET)"

all:	$(LIBNAME)

clean:
	@rm -f $(OBJ) *~ *.gcno *.gcda $(OBJ_SRC_CRIT) $(OBJ_CRIT) #*#
	@echo -e "[$(YELLOW)Cleaned $(LIBNAME)$(RESET)]"

fclean: clean
	@rm -f $(BUILD_PATH)$(LIBNAME)
	@rm -f unit-tests
	@echo -e "[$(YELLOW)Fcleaned $(LIBNAME)$(RESET)]"

re: fclean all

tests_run: $(CFLAGS) += $(CRITFLAGS)
tests_run: $(OBJ_CRIT)
	@gcc -o unit-tests $(SRC) $(OBJ_CRIT) $(CFLAGS) $(CRITFLAGS)
	@echo -e "[$(GREEN)Launch tests $(LIBNAME)$(RESET)]"
	@./unit-tests

.PHONY: all clean fclean re

-include $(DEPS)
