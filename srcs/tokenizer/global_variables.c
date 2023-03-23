
#include "./../../includes/minishell.h"

static char	*ft_strdup_no_quotes(const char *s1)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;


	res = malloc(sizeof(char) * (ft_strlen(s1) + 1 - 2));
	if (!res)
		return (res);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] != '\"')
		{
			res[j] = s1[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	replace_dollar_sign(t_env_var **globals, t_word *word)
{
	t_env_var	*current_global;
	char		*tmp;

	tmp = word->word;
	current_global = *globals;
	if (word->word[0] == '\"')
	{
		free(word->word);
		word->word = ft_strdup_no_quotes(tmp);
	}
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