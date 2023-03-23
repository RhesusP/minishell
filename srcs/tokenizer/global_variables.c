
#include "./../../includes/minishell.h"

static char	*cpy_dollar_value(char *word, int dollar_position)
{
	int		size;
	int		after_dollar;
	char	*res;

	after_dollar = dollar_position + 1;
	while (word[dollar_position + 1] || word[dollar_position + 1] != '\'')
	{
		size++;
		dollar_position++;
	}
	res = calloc(size, sizeof(char));
	size = 0;
	while (word[after_dollar] || word[after_dollar] != '\'')
	{
		res[size] = word[after_dollar];
		size++;
		after_dollar++;
	}
	return (res);
}

static char	*get_dollar_key(char *word)
{
	int		i;
	char	*res;

	i = 0;
	while (word[i] && (word[i] != '\"' || word[i] != '$'))
		i++;
	if (word[i] == '\"')
		return (NULL);
	else if (word[i] == '$')
		res = cpy_dollar_value(word, i);
	return (res);
}

void	replace_dollar_sign(t_env_var **globals, t_word *word)
{
	t_env_var	*current_global;
	char		*dollar_key;

	//dollar_key = get_dollar_key(word->word);
	//printf("dollar key	%s\n", dollar_key);
	current_global = *globals;
	while (current_global)
	{
		if (ft_strcmp(word->word + 1, current_global->key) == 0)
		{
			free(word->word);
			word->word = ft_strdup(current_global->values[0]);
			return ;
		}
		current_global = current_global->next;
	}
}

void	replace_global_variables(t_env_var **globals, t_word **words_lst)
{
	t_word	*current;

	current = *words_lst;
	while (current)
	{
		if (ft_strchr(current->word, '$'))
		{
			if (current->word[0] == '\'' && current->word[ft_strlen(current->word) - 1] == '\'')
				printf("No replacement\n");
			else
				replace_dollar_sign(globals, current);
		}
		current = current->next;
	}
}