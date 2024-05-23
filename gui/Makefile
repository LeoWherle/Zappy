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
BUILD_PATH = build/
CC = g++

RULE =
# used with make DEBUG=n
ifeq ($(DEBUG), n)
	CFLAGS += -O2
	RULE = "DEBUG=n"
	BUILD_PATH := $(BUILD_PATH)release/
# used with make DEBUG=y
else ifeq ($(DEBUG), y)
	LDFLAGS += -fsanitize=address -fsanitize-address-use-after-scope
	CFLAGS += -g3 -DDEBUG  -fsanitize=address
	RULE = "DEBUG=y"
	BUILD_PATH := $(BUILD_PATH)asan/
else
	CFLAGS += -g
	BUILD_PATH := $(BUILD_PATH)debug/
endif

SRC_GUI = 	$(shell find src/ -name "*.cpp" -type f)
OBJ_GUI = 	$(SRC_GUI:%.cpp=$(BUILD_PATH)%.o)
DEPS_GUI = 	$(OBJ_GUI:%.o=%.d)

#LIBINC = $(addsuffix /include, $(addprefix -I, $(LIBS)))
LIB_FLAGS = -Lraylib/src $(addprefix -l, $(LIBS))
RAYLIB_FLAGS = -lGL -lm -lpthread -ldl -lrt -lX11
RAYLIB_DIR = raylib/src

CFLAGS += -W -Wall -Wextra

CFLAGS += -Iraylib_cpp/include/

LDFLAGS += $(LIB_FLAGS) $(RAYLIB_FLAGS)
CRITFLAGS = -lcriterion --coverage


$(BUILD_PATH)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: app

$(BUILD_PATH)$(BIN): lib_build $(OBJ_GUI)
	$(CC) -o $(BUILD_PATH)$(BIN) $(OBJ_GUI) $(LDFLAGS)
	@echo -e "$(GREEN)✓ Compiled $(BIN)$(RESET)"

app: $(BUILD_PATH)$(BIN)
	cp $(BUILD_PATH)$(BIN) .

clean:
	@rm -f $(BUILD_DIR)asan $(BUILD_DIR)debug $(BUILD_DIR)release

fclean: clean
	@rm -f unit-tests
	@rm -f $(BIN)
	@rm -f $(BUILD_DIR)asan/$(BIN)
	@rm -f $(BUILD_DIR)debug/$(BIN)
	@rm -f $(BUILD_DIR)release/$(BIN)

re: fclean all

#tests_run:
#	@for i in $(LIBS); do $(MAKE) -C $$i tests_run; done

.PHONY: all clean fclean re debug tests_run lib_build
.NOTPARALLEL: re