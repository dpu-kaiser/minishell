################################################################################
################################## VARIABLES ###################################
################################################################################

################################################################################
################################## VARIABLES ###################################
################################################################################

NAME    := minishell

CC      =  cc
CFLAGS  =  -Wall -Wextra -g
LIB_DIR = lib
LIBS    =  -L $(LIB_DIR)/libft -lft -lreadline
HEADERS =  -I include -I $(LIB_DIR)/libft

VPATH   := src
SRC     := main.c debug_tools.c init.c signal_handling.c repl.c new_token.c \
           free_token.c new_node.c free_node.c tokenizer.c parser.c \
           parse_cmd.c collect_redirs.c print_ast.c interpreter.c env.c \
           get_cmd_path.c env_to_strlst.c execute_cmd.c format_string.c \
		   builtins_part_one.c builtins_part_two.c env_tools.c error.c \
		   read_heredoc.c create_files.c builtins_part_three.c handle_redir.c \
		   praise_the_norme.c

OBJ_DIR := _obj
OBJ     := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

################################################################################
#################################### RULES #####################################
################################################################################

all: libs $(NAME)

libs:
	@make -C $(LIB_DIR)/libft

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@ $(HEADERS) $(LIBS) 
	@echo "[$(NAME)] Created binary."

$(OBJ_DIR)/%.o: %.c
	@if [ ! -d "$(dir $@)" ]; then \
		mkdir -p $(dir $@); \
	fi
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
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

debug: CFLAGS += -g
debug: CFLAGS += -fsanitize=address -fsanitize=undefined \
				 -fno-sanitize-recover=all -fsanitize=float-divide-by-zero \
				 -fsanitize=float-cast-overflow -fno-sanitize=null \
				 -fno-sanitize=alignment -fno-sanitize=object-size \
				 -fno-sanitize=vptr -fno-sanitize=return -fno-sanitize=signed-integer-overflow \
				 -fno-sanitize=bounds -fno-sanitize=pointer-subtract -fno-sanitize=pointer-compare
debug: CFLAGS += -DDEBUG=1
debug: clean all

.PHONY: all clean fclean re libs debug

################################################################################
################################################################################
