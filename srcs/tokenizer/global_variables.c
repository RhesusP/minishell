
#include "./../../includes/minishell.h"


void	replace_dollar_sign(t_env_var **globals, t_word *word)
{
	t_env_var	*current;

	current = *globals;
	while (current)
	{
		if (strcmp(word->word, current->key))
		{
			free(word->word);
			word->word = ft_strdup(current->values[0]);
			return ;
		}
		current = current ->next;
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