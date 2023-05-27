NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -pthread
RM = rm -f
SRC =	main.c \
			init.c \
			routine.c \
			action.c \
			super_watchman.c \
			utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re