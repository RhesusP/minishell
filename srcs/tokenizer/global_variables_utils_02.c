
#include "./../../includes/minishell.h"

/**
 * @brief check if the global variable exists
 * @return ft_strlen of the value of the VAR if it exists, else returns 0
*/
int	check_var_size(t_env_var **globals, char *word, int i)
{
	char		*key;
	t_env_var	*current;

	current = *globals;
	key = copy_var_key(word, i);
	while (current)
	{
		if (ft_strcmp(key, current->key))
		{
			free(key);
			return (ft_strlen(current->values[0]));
		}
		current = current->next;
	}
	free(key);
	return (0);
}

void	replace_in_copy(int *i, int *j, char *value, char *word_cpy)
{
	int	k;

	k = 0;
	if (value)
	{
		while (value[k])
		{
			word_cpy[*j] = value[k];
			*j = *j + 1;
			k++;
		}
	}
}

/**
 * @brief Flag = 1 if we are between ' ' // Flag = 0 if we are not between ' '
 * 		  Flag = 2 if we are between " "
*/
void	update_flag_quotes(char c, int *flag_quotes)
{
	if (c == '\"')
	{
		if (*flag_quotes == 0)
			*flag_quotes = 2;
		else if (*flag_quotes == 2)
			*flag_quotes = 0;
	}
	else if (c == '\'')
	{
		if (*flag_quotes == 0)
			*flag_quotes = 1;
		else if (*flag_quotes == 1)
			*flag_quotes = 0;
	}
}
