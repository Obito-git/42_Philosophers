NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread
LIBFT=$(SRC_PATH)libft_utils/
SRC_PATH=src/

SRCS = $(SRC_PATH)philo.c $(SRC_PATH)parsing.c $(SRC_PATH)struct_utils.c $(SRC_PATH)algo.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): lib $(OBJS)
		$(CC) -o $(NAME) $(OBJS) libft/libft.a $(CFLAGS)

lib:
		$(MAKE) -C libft/

clean:
	rm -f $(OBJS)
	rm -f $(SRC_PATH).*.swp
	rm -f .*.swp
	rm -f a.out
	$(MAKE) clean -C libft/

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

.PHONY: all clean fclean re bonus
