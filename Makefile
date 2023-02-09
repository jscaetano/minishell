# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 17:50:46 by joacaeta          #+#    #+#              #
#    Updated: 2023/02/09 19:19:37 by joacaeta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
FLAGS := -Wall -Wextra -Werror -fsanitize=address -g
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
	$(CC) $(FLAGS) $^ -o $@ $(INCLUDES) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	rm -f *.gch

run: re
	./minishell

.PHONY: libft all bonus clean fclean re
