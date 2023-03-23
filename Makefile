LIBFT	= libft/libft.a
NAME	= minishell
SRCS	= $(wildcard ./srcs/*.c)
OBJS	= $(SRCS:.c=.o)
CFLAGS	= -Wall -Wextra -Werror -I./readline_installed/include -I./brew/opt/readline_installed/include
LINKER	= -L./readline_installed/lib -lreadline
CC		= cc
RD		= ${shell find ${HOME} -name readline_installed 2>/dev/null}
RM		= rm -f

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		 $(MAKE) -C libft
		 cp libft/libft.a $(NAME)
		 $(CC) $(CFLAGS) $(LINKER) $(OBJS) -o $(NAME) 

clean:
	$(MAKE) clean -C libft
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean -C libft
	rm -rf $(NAME)

install:
	cd readline-8.1 && make clean && ./configure --prefix=${RD} && make && make install

re: fclean all

.PHONY: all clean fclean re
