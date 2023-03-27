#include "minishell.h"

static void	helper(t_token *tokens, int *i, char c)
{
	tokens->quote[*i] = '1';
	while (tokens->value[++(*i)] != c)
		tokens->quote[*i] = '0';
	tokens->quote[*i] = '1';
}

void	quote_counting(t_token *tokens)
{
	int		i;

	i = -1;
	if (tokens != 0)
	{
		while (tokens->value[++i] != '\0')
		{
			if (tokens->value[i] == '\'')
				helper(tokens, &i, '\'');
			else if (tokens->value[i] == '\"')
				helper(tokens, &i, '\"');
			else
				tokens->quote[i] = '0';
		}
	}
}