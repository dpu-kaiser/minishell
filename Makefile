################################################################################
################################## VARIABLES ###################################
################################################################################

NAME    := minishell

CC      =  cc
CFLAGS  =  -Wall -Wextra -Werror
LIB_DIR = lib
LIBS    =  -L $(LIB_DIR)/libft -lft -lreadline
HEADERS =  -I include -I $(LIB_DIR)/libft

VPATH   := src
SRC     := main.c init.c signal_handling.c repl.c

OBJ_DIR := _obj
OBJ     := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

################################################################################
#################################### RULES #####################################
################################################################################

all: libs $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(HEADERS) $(LIBS) $^ -o $@
	@echo "[$(NAME)] Created binary."

libs:
	@make -C $(LIB_DIR)/libft

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
	@make fclean -C $(LIB_DIR)/libft

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		rm -f $(NAME); \
		echo "[$(NAME)] Removed binary."; \
	fi

re:	fclean all

.PHONY: all clean fclean re libs

################################################################################
################################################################################
