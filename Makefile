NAME    = philo
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread -g
SRCS    = main.c actions.c routine.c makers.c
OBJS    = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
