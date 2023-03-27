#include "./../../includes/minishell.h"

/**
 * @brief Flag = 1 if we are between ' ' // Flag = 0 if we are not between ' '
*/
void	update_flag_quotes(char c, int *flag_quotes)
{
	if (c == '\'')
	{
		if (*flag_quotes == 0)
			*flag_quotes = 1;
		else if (*flag_quotes == 1)
			*flag_quotes = 0;
	}
}
/**
 * @brief Counts the maximum size of the values in the global variable structure
 * @return Max size 
**/
int	max_size_global_var(t_env_var **globals)
{
	t_env_var	*current;
	int			max_size;
	int			current_size;

	current = *globals;
	max_size = 0;
	current_size = 0;
	while (current)
	{
		current_size = ft_strlen(current->values[0]);
		if (current_size > max_size)
			max_size = current_size;
		current = current->next;
	}
	return (max_size);
}

/**
 * @brief Counts the number of unquoted $ in the char *
**/
int	count_unquoted_dollars(char *word)
{
	int		flag_quotes;
	int		i;
	int		dollars;

	i = 0;
	flag_quotes = 0;
	dollars = 0;
	while (word[i])
	{
		if (word[i] == '\'')
		{
			if (flag_quotes == 0)
				flag_quotes = 1;
			else if (flag_quotes == 1)
				flag_quotes = 0;
		}
		if (word[i] == '$' && flag_quotes == 0)
			dollars++;
		i++;
	}
}