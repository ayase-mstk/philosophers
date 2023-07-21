NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS_DIR = srcs/
SRCS = philo_bonus.c \
		philo_routine.c \
		philo_action.c \
		utils.c \
		utils2.c

OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

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