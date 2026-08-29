CC = cc
FLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c print_hexa.c print_ptr.c print_char.c print_nbr.c print_unsigned.c
SRC_OBJ = $(SRC:.c=.o)
NAME = libftprintf.a

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(SRC_OBJ)
	@cp $(LIBFT) $(NAME)
	@ar rcs $(NAME) $^

$(LIBFT):
	@make -C $(LIBFT_PATH) all --no-print-directory

%.o: %.c
	@$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@rm -f $(SRC_OBJ)

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)

re: fclean all

test:
	sh compile.sh

.PHONY: all clean fclean re test
