NAME = philo/philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g -pthread
RM = rm -rf
SRCS_DIR = philo/srcs/
SRCS =	main.c \
		init.c \
		routine.c \
		action.c \
		super_watchman.c \
		utils.c

OBJ_DIR = philo/obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)%.o: $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re