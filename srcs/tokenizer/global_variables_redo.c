
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

/**
 * @brief Find the size need for the malloc of word_cpy
**/
int	copy_memory(t_env_var **globals, char *word)
{
	int	i;
	int	size;
	int	flag_quotes;


	i = 0;
	flag_quotes = 0;
	while (word[i])
	{
		update_flag_quotes(word[i], &flag_quotes);
		if (flag_quotes == 1 || word[i] != '$')
		{
			size++;
			i++;
		}
		if (flag_quotes != 1 && word[i] == '$')
		{
			i++;
			size += check_var_size(globals, word, i);
			while (check_var_end(word[i]) == FAILURE)
				i++;
		}
	}
	return (size);
}

/**
 * @return the value of the $VAR // NULL if there is no value associated
*/
char	*var_value(t_env_var **globals, char *word, int i)
{
	char		*key;
	t_env_var	*current;

	current = *globals;
	key = copy_var_key(word, i);
	printf("#### KEY ####\n     %s\n", key);
	while (current)
	{
		if (ft_strcmp(key, current->key) == 0)
		{
			free(key);
			return (current->values[0]);
		}
		current = current->next;
	}
	free(key);
	return (0);
}

/**
 * @brief copy the string with replacement of $VAR
**/
void	copy_filling(t_env_var **globals, char *word, char *word_cpy)
{
	int		i;
	int		j;
	int		k;
	int		flag_quotes;
	char	*value;

	i = 0;
	j = 0;
	flag_quotes = 0;
	while (word[i])
	{
		//printf("word[i] == %c\n", word[i]);
		update_flag_quotes(word[i], &flag_quotes);
		//printf("flag == %d\n", flag_quotes);
		if (flag_quotes == 1 || word[i] != '$')
		{
			word_cpy[j] = word[i];
			i++;
			j++;
		}
		if (flag_quotes != 1 && word[i] == '$')
		{
			i++;
			value = var_value(globals, word, i);
			if (value)
			{
				k = 0;
				while (value[k])
				{
					word_cpy[j] = value[k];
					j++;
					k++;
				}
			}
			while (check_var_end(word[i]) == FAILURE)
				i++;
		}
	}
}


void	replace_global_variables(t_env_var **globals, t_word **words_lst)
{
	t_word	*current;
	char	*word_cpy;

	current = *words_lst;
	while (current)
	{
		word_cpy = calloc(copy_memory(globals, current->word), sizeof(char));
		copy_filling(globals, current->word, word_cpy);
		free(current->word);
		current->word = ft_strdup(word_cpy);
		free(word_cpy);
		current = current->next;
	}
}