# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bpeeters <bpeeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/20 10:39:17 by bpeeters      #+#    #+#                  #
#    Updated: 2020/09/20 10:39:24 by bpeeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
DEBUG = debug
SRC = main.c philosophers.c philo_eat.c philo_write.c philo_utils.c \
		mutex.c get_time.c initialize.c free_philo.c utils.c
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
