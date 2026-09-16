CC = cc
FLAGS = -Wall -Wextra -Werror
HASH_TESTER = tester/hash_tester.sh
SRC_PATH = src/hash/
SRC = $(SRC_PATH)utils.c $(SRC_PATH)main.c $(SRC_PATH)md5_tables.c \
      $(SRC_PATH)sha256_tables.c $(SRC_PATH)sha256.c $(SRC_PATH)md5.c \
      $(SRC_PATH)parsing.c $(SRC_PATH)hashing.c
BONUS_SRC = $(SRC_PATH)whirlpool.c $(SRC_PATH)whirlpool_tables.c
ALL_SRC = $(SRC) $(BONUS_SRC)
SRC_OBJ = $(SRC:.c=.o)
SRC_BONUS_OBJ = $(BONUS_SRC:.c=.o)
ALL_OBJ = $(SRC_OBJ) $(SRC_BONUS_OBJ)
NAME = ft_ssl
LIBFT_PATH = src/ft_printf
LIBFT = $(LIBFT_PATH)/libftprintf.a

all: $(NAME)

$(NAME): $(LIBFT) $(ALL_OBJ)
	@$(CC) $(FLAGS) $(ALL_OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH) all --no-print-directory

%.o: %.c
	@$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	@make -C $(LIBFT_PATH) clean --no-print-directory
	@rm -f $(ALL_OBJ)

fclean: clean
	@make -C $(LIBFT_PATH) fclean --no-print-directory
	@rm -f $(NAME)

re: fclean all

test:
	bash $(HASH_TESTER)

.PHONY: all clean fclean re test
