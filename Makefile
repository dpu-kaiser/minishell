################################################################################
################################## VARIABLES ###################################
################################################################################

NAME    := minishell

CC      =  cc
CFLAGS  =  -Wall -Wextra -Werror
HEADERS =  -Iinclude

VPATH   := src
SRC     := main.c debug-tools.c

OBJ_DIR := _obj
OBJ     := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

################################################################################
#################################### RULES #####################################
################################################################################

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(HEADERS) $^ -o $@
	@echo "[$(NAME)] Created binary."

$(OBJ_DIR)/%.o: %.c
	@if [ ! -d "$(dir $@)" ]; then \
		mkdir -p $(dir $@); \
	fi
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "[$(NAME)] Compiled $<."

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		rm -rf $(OBJ_DIR); \
		echo "[$(NAME)] Removed object files."; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "[$(NAME)] Removed binary."; \
	fi

re:	fclean all

debug: CFLAGS += -g
debug: CFLAGS += -fsanitize=address -fsanitize=undefined \
				 -fno-sanitize-recover=all -fsanitize=float-divide-by-zero \
				 -fsanitize=float-cast-overflow -fno-sanitize=null \
				 -fno-sanitize=alignment
debug: CFLAGS += -DDEBUG=1
debug: clean all

.PHONY: all clean fclean re debug

################################################################################
################################################################################
