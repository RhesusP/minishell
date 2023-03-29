#include "./../../includes/minishell.h"

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

/**
 * @brief Check if the character can mark the end of the $VAR
 * @return SUCCESS if a limit character was found, FAILURE if not
*/
int	check_var_end(char c)
{
	if (c == '\"' || c == '\'' || c == '$' || c == ' ' || c == '\0')
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief Make a copy of $KEY without the dollar
**/
char	*copy_var_key(char *word, int i)
{
	char	*key;
	int		j;

	key = calloc(allocate_key_memory(word, i), sizeof(char));
	j = 0;
	while (check_var_end(word[i]) == FAILURE)
	{
		key[j] = word[i];
		j++;
		i++;
	}
	return (key);
}

/**
 * @brief Allocate memory to make a copy of $KEY without the dollar
**/
int	allocate_key_memory(char *word, int i)
{
	int	size;

	size = 0;
	while (check_var_end(word[i]) == FAILURE)
	{
		i++;
		size++;
	}
	return (size);
}