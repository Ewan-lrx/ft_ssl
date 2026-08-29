CC = cc
FLAGS = -Wall -Wextra -Werror
HASH_TESTER = tester/hash_tester.sh
SRC_PATH = src/hash/
SRC = $(SRC_PATH)utils.c $(SRC_PATH)main.c $(SRC_PATH)md5_tables.c \
      $(SRC_PATH)sha256_tables.c $(SRC_PATH)sha256.c $(SRC_PATH)md5.c \
      $(SRC_PATH)parsing.c $(SRC_PATH)hashing.c
SRC_OBJ = $(SRC:.c=.o)
NAME = ft_ssl
LIBFT_PATH = src/ft_printf
LIBFT = $(LIBFT_PATH)/libftprintf.a

all: $(NAME)

$(NAME): $(LIBFT) $(SRC_OBJ)
	@$(CC) $(FLAGS) $(SRC_OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) all --no-print-directory

%.o: %.c
	@$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@rm -f $(SRC_OBJ)

fclean: clean
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -f $(NAME)

re: fclean all

test:
	sh $(HASH_TESTER)

.PHONY: all clean fclean re test
