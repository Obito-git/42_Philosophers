NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
LIBFT=libft/
SRC_PATH=src/

SRCS =	$(SRC_PATH)philo.c $(SRC_PATH)parsing.c $(SRC_PATH)struct_utils.c \
		$(SRC_PATH)algo.c $(SRC_PATH)threads.c $(SRC_PATH)operations.c \
		$(LIBFT)ft_atol_sample.c $(LIBFT)ft_strlen.c $(LIBFT)ft_pow.c \
		$(LIBFT)ft_isdigit.c $(LIBFT)ft_strcmp.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	rm -f $(OBJS)
	rm -f $(SRC_PATH).*.swp
	rm -f .*.swp
	rm -f a.out

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
