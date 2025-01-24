NAME = 				minishell

CC = 				cc
CFLAGS = 			-g -Wall -Wextra -Werror

GREEN = 			\\033[0;32m
YELLOW = 			\\033[0;33m
RED = 				\\033[0;31m
BLUE = 				\\033[0;34m
MAGENTA = 			\033[0;35m
CYAN = 				\033[0;36m
RESET = 			\\033[0m

LIBFT_DIR =			libft
INCLUDES =			includes/
SRC_DIR =			src/
OBJ_DIR =			obj/

LEXER_DIR =			lexer/
LEXER_FILES =		lexer.c lexer_utils.c

UTILS_DIR =			utils/
UTILS_FILES =		check_syntax.c handle_error.c quote_handler.c free_func.c check_token.c env_utils.c

LIST_HANDLE_DIR =	utils/list_handle/
LIST_HANDLE_FILES =	getter.c setter.c lst_add_back.c lst_init.c lst_clear.c

DEBUG_DIR =			_debug/
DEBUG_FILES =		debug_token.c debug_cmd.c

PARSER_DIR =		parser/
PARSER_FILES =		clean_word_token.c fill_cmd.c heredoc_handle.c parse_redirection.c expand_env_var.c

EXEC_DIR =			exec/
EXEC_FILES =		exec.c cmd_manager.c pipes_manager.c set_redirection.c

BUILTIN_DIR =		exec/builtins/
BUILTIN_FILES = 	pwd.c builtins_handler.c env.c cd.c export.c export_utils.c unset.c exit.c

SRC_FILES = main.c \
			$(addprefix $(LEXER_DIR), $(LEXER_FILES)) \
			$(addprefix $(UTILS_DIR), $(UTILS_FILES)) \
			$(addprefix $(DEBUG_DIR), $(DEBUG_FILES)) \
			$(addprefix $(PARSER_DIR), $(PARSER_FILES)) \
			$(addprefix $(EXEC_DIR), $(EXEC_FILES)) \
			$(addprefix $(BUILTIN_DIR), $(BUILTIN_FILES)) \
			$(addprefix $(LIST_HANDLE_DIR), $(LIST_HANDLE_FILES))

OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

# setup:
# 	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(LEXER_DIR) \
# 	$(DEBUG_DIR)/$(DEBUG_FILES)

$(LIBFT):
	@echo "$(CYAN)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)Program $(NAME) has been created.$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I $(INCLUDES) -I $(LIBFT_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(YELLOW)Object files removed.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo  "$(RED)Program $(NAME) has been deleted.$(RESET)"

re: fclean all

.PHONY: all clean fclean re