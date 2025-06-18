CC = cc
CFLAGS = -Wall -Werror -Wextra

SRC = main.c parse_input.c routine.c init.c time.c print.c clean.c utils.c death.c threads.c \
		monitor.c

OBJS = $(SRC:.c=.o)

NAME = philo_bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re