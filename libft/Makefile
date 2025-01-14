NAME = libft.a
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

GREEN = \\033[0;32m
YELLOW = \\033[0;33m
RED = \\033[0;31m
BLUE = \\033[0;34m
CYAN = \\033[0;36m
RESET = \\033[0m

SRC = 				ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isprint.c \
					ft_strchr.c \
					ft_strlen.c \
					ft_tolower.c \
					ft_toupper.c \
					ft_strrchr.c \
					ft_memset.c \
					ft_memcpy.c \
					ft_bzero.c \
					ft_memmove.c \
					ft_strncmp.c \
					ft_strlcpy.c \
					ft_memchr.c \
					ft_strlcat.c \
					ft_memcmp.c \
					ft_strnstr.c \
					ft_atoi.c \
					ft_atol.c \
					ft_strdup.c \
					ft_calloc.c \
					ft_strjoin.c \
					ft_putchar_fd.c \
					ft_substr.c \
					ft_strtrim.c \
					ft_itoa.c \
					ft_strmapi.c \
					ft_striteri.c \
					ft_putstr_fd.c \
					ft_putendl_fd.c \
					ft_split.c \
					ft_putnbr_fd.c \
					ft_printf/ft_printf_utils.c \
					ft_printf/ft_printf.c \
					ft_prepend_char.c \
					get_next_line.c \
					get_next_line_utils.c

OBJ = $(SRC:.c=.o)

SRC_BONUS = ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c \
			
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_BONUS)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(GREEN)Library $(NAME) created.$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	@$(RM) $(NAME)
	@echo  "$(RED)Library $(NAME) removed.$(RESET)"

bonus: $(OBJ) $(OBJ_BONUS)
	$(AR) $(NAME) $(OBJ) $(OBJ_BONUS)

re : fclean all

.PHONY: all clean fclean re bonus