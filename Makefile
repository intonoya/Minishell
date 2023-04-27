NAME = minishell

PREFIX = $(shell find ${HOME} -name readline-intonoya 2>/dev/null)

CC = cc

RM = rm -rf

FLAGS = -Wall -Wextra -Werror

MKDIR = mkdir -p

OBJS_DIR = OBJS

SRCS = $(wildcard *.c) $(wildcard builtins/*.c)  $(wildcard parsing/*.c)  \
$(wildcard signals/*.c)  $(wildcard redirections/*.c)  $(wildcard utils/*.c)

_OBJS = $(patsubst %.c, %.o, $(SRCS))

OBJS = $(patsubst %.o, $(OBJS_DIR)/%.o, $(_OBJS))

INCLUDES = -I./readline-intonoya/include

LINKERS	= -L./readline-intonoya/lib -lreadline

$(OBJS_DIR)/%.o: %.c
	@ $(MKDIR) $(OBJS_DIR)/builtins
	@ $(MKDIR) $(OBJS_DIR)/parsing
	@ $(MKDIR) $(OBJS_DIR)/redirections
	@ $(MKDIR) $(OBJS_DIR)/utils
	@ $(MKDIR) $(OBJS_DIR)/signals
	@$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(NONE)
	@$(CC) $(FLAGS) $(OBJS) $(LINKERS) $(INCLUDES) -o $(NAME)
	$(NONE)

clean:
	$(NONE)
	@ $(RM) $(OBJS_DIR)

fclean: clean
	$(NONE)
	@ $(RM) $(NAME)

re: fclean all

readline:
	cd readline-master && make clean && ./configure --prefix=$(PREFIX) && make && make install

norm:
	clear
	norminette $(SRCS) minishell.h

wc:
	clear
	wc -l $(SRCS)

.PHONY: all clean fclean re readline norm wc
