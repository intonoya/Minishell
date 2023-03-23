#ifndef	MINISHELL_H
# define MIISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/resource.h>
# include "libft/libft.h"
# include <dirent.h> 
# include <sys/ioctl.h>

typedef struct s_var
{
	char			*name;
	char			*value;
	char			meaning;
	int				status;
	struct s_var	*next;
}					t_var;

typedef struct s_token
{
	char			type;
	char			*value;
	char			*quote;
	struct s_token	*next;
}					t_token;

typedef struct s_command
{
	int					id;
	char				**args;
	char				*path;
	int					path_error;
	char				*oper;
	char				*oper_value;
	char				delimitor;
	int					builtin;
	int					std_in;
	int					std_in_dup1;
	int					std_out;
	int					std_out_dup1;
	int					std_err;
	int					pipe;
	int					pipe_out;
	int					pipe_in;
	struct s_command	*next;
}						t_command;

#endif