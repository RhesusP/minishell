
#include "./../../includes/minishell.h"
/*
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

char	*cpy_dollar_value(char *word, int i)
{
	int		dollar_pos;
	int		malloc_size;
	char	*res;

	malloc_size = 0;
	dollar_pos = i;
	while(word[i] || word[i] != '\"')
	{
		malloc_size++;
		i++
	}
	i = 0;
	res = calloc(malloc_size + 1, sizeof(char));
	while (word[dollar_pos] || word[dollar_pos] != '\"')
	{
		res[i] = word[dollar_pos];
		i++;
		dollar_pos++;
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
	{
		res = cpy_dollar_value(word, i);
	}
	return (res);
}
*/
////////////////////////////////////////////////

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

/* OLD FUNCTION*/
void	replace_global_variables(t_env_var **globals, t_word **words_lst)
{
	t_word	*current;

	current = *words_lst;
	//Il faudrait compter le nombre de $ total dans la phrase
	//Il faut à chaque fois check si on est entre guillemets
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
//////////////////////////////////////////////////////////////////
/**
 * @brief Count the number of dollar signs to know how many $VAR we have
 * Doesn't count the $ if there are no char after it
*/
int	count_dollar_nbr(char *word)
{
	int	i;
	int	dollar_nbr;

	i = 0;
	dollar_nbr = 0;
	while (word[i])
	{
		if (word[i] == '$' && word[i + 1])
			dollar_nbr++;
		i++
	}
	return (dollar_nbr);
}

/**
 * @brief Check if the $VAR is in between quotes ' ' or not
 * @return FAILURE if no quotes // SUCCESS if quotes
*/
int	check_quotes(char *word, int dollar_pos)
{
	int	cpy;
	int	flag;

	cpy = dollar_pos;
	flag = 0;
	if (dollar_pos = 0)
		return (FAILURE);
	while (word[cpy])
	{
		if (word[cpy] == '\'')
		{
			flag = 1;
			break ;
		}
		cpy--;
	}
	if (flag == 1)
	{
		while (word[dollar_pos])
		{		
			if (word[dollar_pos] == '\'')
			{
				flag = 2;
				break ;
			}
			dollar_pos--;
		}
	}
	if (flag == 2)
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief Replace the $VAR, but not if there is '$VAR '
*/
void	replace_dollar_sign(char *word, int dollar_pos)
{
	if (check_quotes(word, dollar_pos) == FAILURE)
	{
		// Copie / strdup de ce qu'on a avant le $ étudié
		// replace_dollar_sign --> on arrête le remplacement quand on rencontre :
		// 		- Fin du mot
		// 		- Un guillemet simple ou double
		// 		- Un autre signe $
		// Copie de ce qu'on a aprèsle dollar étudié
	}

}

/* NEW FUNCTION*/
/**
 * @brief Check each $VAR and replace it if necessary by its value
*/
void	replace_global_variables(t_env_var **globals, t_word **words_lst)
{
	t_word	*current;
	int		dollar_nbr;
	int		i;
	int		j;


	current = *words_lst;
	while (current)
	{
		dollar_nbr = count_dollar_nbr(current->word);
		j = 0;
		i = 0;
		while (i < dollar_nbr)
		{
			while (current->word[j] != '$')
				j++;
			replace_dollar_sign(current->word, j);
		}
	}
	//Il faudrait compter le nombre de $ total dans la phrase
	//Il faut à chaque fois check si on est entre guillemets

}


/*AUTRE IDEE --> remplacement au fur et à mesure
	- On avance dans le mot
	- A chaque fois qu'on rencontre un $ on stoppe, on regarde dans la strucutre par quoi on le remplace
	- Si on rencontre un ' : on met un flag = 1 jusqu'à ce qu'on rencontr le prochain
	- Quand flag = 1, on ne remplace pas les $
	- Quand on rencontre le second ', on repasse le flag = 0
*/





/**
 * @brief look if there is any corresponding global variable to the $VAR
 * @return NULL if no match is found, else t_env_var * of the key found 
*/
t_env_var	*look_for_global_var(char *word, t_env_var **globals, int i)
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
			return (current);
		}
		current = current->next;
	}
	free(key);
	return (NULL);
}

/**
 * @brief copy the translation of $VAR into the new string
*/
void	copy_global_var(t_env_var *global_var, char *word_cpy, int *j)
{
	int	i;

	i = 0;
	while (global_var->values[0][i])
	{
		word_cpy[*j] = global_var->values[0][i];
		i++;
		*j++;
	}
}

void	replace_global_variables(t_env_var **globals, t_word **words_lst)
{
	t_word		*current;
	t_env_var	*global_found;
	int			flag_quotes;
	int			i;
	int			j;
	char		*word_cpy;

	current = *words_lst;
	while (current)
	{
		i = 0;
		j = 0;
		flag_quotes = 0;
		word_cpy = calloc(ft_strlen(current->word) + (count_unquoted_dollars(current->word) * max_size_global_var(globals)));
		while (current->word[i])
		{
			update_flag_quotes(current->word[i], &flag_quotes);
			if (current->word[i] == '$' && flag_quotes == 0)
			{
				global_found = look_for_global_var(current->word, globals, i); //Not sure of return value
				copy_global_var(global_found, word_cpy, &j);
				while (current->word[i] != )
			}
				//replace dollar sign
			i++;
		}
		current = current->next;
	}
}

//////////////////////
/**
 * @brief	Finds the size needed to malloc the copy of current->word
*/
int	allocate_copy_memory(t_env_var **globals, char *word)
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
		if (flag_quotes == 0 && word[i] == '$')
		{
			while (word[i] != )
		}
	}
}

void	replace_global_variables(t_env_var **globals, t_word **words_lst)
{
	t_word	*current;

	current = *words_lst;
	while (current)
	{
		allocate_copy_memory();
	}
}