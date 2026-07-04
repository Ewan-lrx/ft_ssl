CC = cc
FLAGS = -Wall -Wextra -Werror
SRC = utils.c main.c
SRC_OBJ = $(SRC:.c=.o)
NAME = ft_ssl
LIBFT_PATH = ./ft_printf
LIBFT = $(LIBFT_PATH)/libftprintf.a

all: $(NAME)

$(NAME): $(LIBFT) $(SRC_OBJ)
	@$(CC) $(FLAGS) $(SRC_OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) all --no-print-directory

%.o: %.c
	@$(CC) $(FLAGS) -I. -c $< -o $@
:q

clean:
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@rm -f $(SRC_OBJ)

fclean: clean
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -f $(NAME)

re: fclean all

test:
	sh compile.sh

.PHONY: all clean fclean re test
