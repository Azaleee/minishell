NAME = 			minishell

CC = 			cc
CFLAGS = 		#-Wall -Wextra -Werror

GREEN = 		\\033[0;32m
YELLOW = 		\\033[0;33m
RED = 			\\033[0;31m
BLUE = 			\\033[0;34m
MAGENTA = 		\033[0;35m
CYAN = 			\033[0;36m
RESET = 		\\033[0m

LIBFT_DIR =		libft
INCLUDES =		includes/
SRC_DIR =		src/
OBJ_DIR =		obj/

LEXER_DIR =		lexer/
LEXER_FILES =	lexer.c lexer_list.c lexer_utils.c

UTILS_DIR =		utils/
UTILS_FILES =	check_syntax.c handle_error.c quote_handler.c

DEBUG_DIR =		_debug/
DEBUG_FILES =	debug_token.c

PARSER_DIR =	parser/
PARSER_FILES =	clean_word_token.c

SRC_FILES = main.c \
			$(addprefix $(LEXER_DIR), $(LEXER_FILES)) \
			$(addprefix $(UTILS_DIR), $(UTILS_FILES)) \
			$(addprefix $(DEBUG_DIR), $(DEBUG_FILES)) \
			$(addprefix $(PARSER_DIR), $(PARSER_FILES)) 
			
OBJ_FILES = $(SRC_FILES:.c=.o)

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

LIBFT = $(LIBFT_DIR)/libft.a

all: setup $(LIBFT) $(NAME)

setup:
	@mkdir -p $(OBJ_DIR) $(OBJ_DIR)/$(LEXER_DIR) \
	$(DEBUG_DIR)/$(DEBUG_FILES)

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