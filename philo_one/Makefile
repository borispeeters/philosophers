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

test:
	./philo_one 4 410 200 200

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
