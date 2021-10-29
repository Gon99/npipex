# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: goliano- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/28 16:03:52 by goliano-          #+#    #+#              #
#    Updated: 2021/10/29 17:10:26 by goliano-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	./utils/ft_strlen.c ./utils/ft_strjoin.c ./utils/ft_substr.c \
		./utils/ft_calloc.c ./utils/ft_memset.c ./srcs/pipex.c \
		./utils/ft_strnstr.c ./utils/ft_strncmp.c ./utils/ft_strtrim.c \
		./utils/ft_split.c ./utils/ft_strcatslash.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

OBJS = $(SRCS:.c=.o)

RM	= rm -f

NAME = pipex

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS)	-o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
