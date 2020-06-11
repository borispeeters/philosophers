# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: anonymous <anonymous@student.codam.nl>       +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/20 04:19:16 by anonymous      #+#    #+#                 #
#    Updated: 2020/03/20 04:19:16 by anonymous     ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one
SRC = main.c utils.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Werror -Wextra
.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	clang $(OBJ) -o $(NAME) -pthread

%.o: %.c
	clang $(CFLAGS) -c $? -o $@

test1:
	./philo_one 5 800 200 200

test2:
	./philo_one 4 410 200 200

test3:
	./philo_one 4 310 200 100

test4:
	./philo_one 2 310 200 100

test:
	./philo_one 4 210 100 100

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
