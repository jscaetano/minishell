# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 17:50:46 by joacaeta          #+#    #+#              #
#    Updated: 2023/01/30 18:43:53 by joacaeta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
FLAGS := -Wall -Wextra -Werror -lreadline -g -fsanitize=address
INCLUDE_DIRS :=	src \
				inc \
				.
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := minishell
SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@ $(INCLUDES)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	rm -f *.gch

run: all
	./minishell

.PHONY: libft all bonus clean fclean re
