CC = cc
FLAGS = -Wall -Wextra -Werror
SRC = ft_strcmp.c ft_isalnum.c ft_isprint.c ft_strdup.c ft_strncmp.c ft_toupper.c ft_isalpha.c ft_memcpy.c \
      ft_strlcat.c ft_strnstr.c ft_atoi.c ft_isascii.c ft_memset.c ft_strlcpy.c ft_strrchr.c \
      ft_bzero.c ft_isdigit.c ft_strchr.c ft_strlen.c ft_tolower.c ft_memmove.c ft_memchr.c \
      ft_memcmp.c ft_calloc.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
      ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRC_BONUS= ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
	   ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
	   ft_lstmap_bonus.c
SRC_OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(SRC_BONUS:.c=.o)
OBJ_ALL= $(SRC_OBJ) $(BONUS_OBJ)
NAME = libft.a

all: $(NAME)

$(NAME): $(SRC_OBJ)
	@ar rcs $(NAME) $^

bonus: $(OBJ_ALL)
	@ar rcs $(NAME) $(OBJ_ALL)

%.o: %.c
	@$(CC) $(FLAGS) -I. -c $< -o $@

clean:
	@rm -f $(OBJ_ALL)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
