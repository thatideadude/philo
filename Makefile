NAME = philo

CFLAGS = -Wall -Wextra -Werror -g

SRCS =	main.c

OBJS = $(SRCS:.c=.o) $(B_SRCS:.c=.o)

.PHONY: all
all: $(NAME) 

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus:	all

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
