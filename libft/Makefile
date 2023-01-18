# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: intonoya <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 14:09:57 by intonoya          #+#    #+#              #
#    Updated: 2022/04/19 15:44:41 by intonoya         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

CC			= cc

CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f

SRCS		= $(wildcard *.c)

BONSRCS		= $(wildcard ft_lst*.c)

OBJS		= $(SRCS:.c=.o)

BONOBJS		= $(BONSRCS:.c=.o)

%.o:%.c
			$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rcs $(NAME) $(OBJS)

bonus:		$(BONOBJS)
			ar rcs $(NAME) $(BONOBJS)
			
clean:
			$(RM) $(OBJS)
			$(RM) $(BONOBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re
