# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bpeeters <bpeeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/20 10:40:32 by bpeeters      #+#    #+#                  #
#    Updated: 2020/09/20 10:40:36 by bpeeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_two
DEBUG = debug
SRC = main.c philosophers.c philo_eat.c philo_write.c ft_usleep.c \
		semaphore.c get_time.c initialize.c free_philo.c utils.c
OBJ = $(SRC:.c=.o)
CC = clang
CFLAGS = -Wall -Werror -Wextra
.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -pthread

debug: $(OBJ)
	$(CC) $(OBJ) -o $(DEBUG) -g -fsanitize=thread

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(DEBUG)

re: fclean all
