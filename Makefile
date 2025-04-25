# Compiler and flags
CC = gcc
CFLAGS =  -pthread #-Wall -Wextra -Werror

# Source files and object files
SRC = philo.c get_time.c init_data.c simulation.c monitor.c
OBJ = $(SRC:.c=.o)

# Output executable
NAME = philo

# Default target
all: $(NAME)

# Linking object files to create the executable
$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

# Rule for compiling .c files to .o
%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ)

# Remove all compiled files
fclean: clean
	rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets (not actual files)
.PHONY: all clean fclean re
