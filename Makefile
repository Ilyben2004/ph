CC = cc #gcc #-Lpthread -fsanitize=thread -g3  #-fsanitize=thread -g3
CFLAGS = -Wall -Wextra -Werror
SRC = philo.c get_time.c init_data.c simulation.c monitor.c  utils.c utils2.c libft.c 
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

.PHONY: all clean fclean re
