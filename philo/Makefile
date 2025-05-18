CC = cc #gcc -Lpthread -fsanitize=thread -g3
CFLAGS = -Wall -Wextra -Werror
SRC = philo.c get_time.c init_data.c simulation.c monitor.c  utils.c libft.c lock_unlock.c ft_do_something.c
OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all