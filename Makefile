CC = gcc -Lpthread -fsanitize=thread -g3  #-fsanitize=thread -g3

SRC = philo.c get_time.c init_data.c simulation.c monitor.c utils.c libft.c 
OBJ = $(SRC:.c=.o)

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
