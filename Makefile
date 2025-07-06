# **************************************************************************** #
#                                  Makefile                                    #
# **************************************************************************** #

NAME        = philo
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -pthread
SRCS        = init.c main.c monitor.c routine.c threads.c utils.c
OBJS        = $(SRCS:.c=.o)
HEADER      = philo.h

# Default rule
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Clean object files
clean:
	rm -f $(OBJS)

# Clean everything (including executable)
fclean: clean
	rm -f $(NAME)

# Recompile from scratch
re: fclean all

.PHONY: all clean fclean re
