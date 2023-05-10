/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:37:25 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/10 18:23:06 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	is_quoted(char *str, char quote)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			nb++;
		i++;
	}
	if (nb == 2)
		return (1);
	return (0);
}

// char	*remove_quotes(char *str, char quote)
// {
// 	int	len_before;
// 	int	len_between;
// 	char	*bef;
// 	char	*bet;
// 	char	*aft;
// 	char 	*res;
// 	char	*temp;

// 	len_before = 0;
// 	while (str[len_before] != '\0' && str[len_before] != quote)
// 		len_before++;
// 	bef = ft_strndup(str, len_before);
// 	len_between = len_before + 1;
// 	while (str[len_between] != '\0' && str[len_between] != quote)
// 		len_between++;
// 	bet = ft_strndup(&str[len_before + 1], len_between - 1 - len_before);
// 	aft = ft_strdup(&str[len_between + 1]);
// 	temp = ft_strjoin(bef, bet);
// 	res = ft_strjoin(temp, aft);
// 	printf("bef: %s\n", bef);
// 	printf("bet: %s\n", bet);
// 	printf("aft: %s\n", aft);
// 	free(temp);
// 	free(bef);
// 	free(bet);
// 	free(aft);
// 	free(str);
// 	return (res);
// }

/**
 * @brief 
 * 
 * @param words_lst 
 * @param global_vars 
 * @param env_vars 
 * @return 0 if not, 1 if " '' ", 2 if ' "" '
 */
int	is_multiple_quoted(char *str)
{
	int	i;
	int	is_single;
	int	is_double;
	int	first;

	i = 0;
	first = 0;
	is_single = 0;
	is_double = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (!first)
				first = 2;
			is_single = 1;
		}
		if (str[i] == '"')
		{
			if (!first)
				first = 1;
			is_double = 1;
		}
		i++;
	}
	if (is_single != 0 && is_double != 0)
		return (first);
	return (0);
}

char	**get_key_name(char *str)
{
	int		len;
	int		i;
	char	**tab;

	printf("\033[31mget key name start with: %s\n\033[39m", str);
	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	tab[0] = ft_strndup(str, i);
	len = i;
	len += 1;
	while (str[len] != '\0' && (str[len] == '_' || str[len] == '?' || ft_isalnum(str[len])))
		len++;
	if (i < ft_strlen(str) - 1)
		tab[1] = ft_strndup(&str[i], len - i);
	else
		tab[1] = 0;
	printf("tab null? %c [%d] (len: %d)\n", str[i], i, len - i);
	printf("POTENTIAL ERR: %s\n", tab[1]);
	if (str[len] && len < ft_strlen(str) - 1)
		tab[2] = ft_strdup(&str[len]);
	else
		tab[2] = 0;
	return (tab);
}

char	*values_to_str(char **tab)
{
	char	*res;
	char	*temp;
	int		i;

	temp = "";
	res = 0;
	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
	{
		if (i > 0)
			temp = ft_strdup(res);
		if (res)
			free(res);
		res = ft_strjoin(temp, tab[i]);
		if (i > 0)
			free(temp);
		i++;
	}
	return (res);
}

char	*get_values(char *key, t_env_var **lst)
{
	t_env_var	*current;
	char		**values;
	int			stop;

	stop = 0;
	if (!*lst || !key)
		return (0);
	if (ft_strcmp(key, "$") == 0)
	{
		printf("key is a dollar symbol\n");
		return ("$");
	}
	else if (ft_strcmp(key, "$?") == 0)
	{
		printf("\033[92mkey IS A QUESTION MARK\n\033[39m");
		return (ft_itoa(g_status));
	}
	key = &key[1];
	current = *lst;
	while (current && !stop)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			values = current->values;
			stop = 1;
		}
		current = current->next;
	}
	return (values_to_str(values));
}

char	*get_vars(char *str, t_env_var **env)
{
	char	**tab;
	char	*res;
	char	*temp;

	printf("\033[31mget var start with: %s\n\033[39m", str);
	if (ft_strlen(str) == 1 && str[0] == '$')
		return (str);
	tab = get_key_name(str);
	printf("before: %s\n", tab[0]);
	printf("key: %s\n", tab[1]);
	printf("after: %s\n", tab[2]);
	if (tab[1])
		res = ft_strjoin(tab[0], get_values(tab[1], env));
	else
		res = ft_strjoin(tab[0], "");
	while (tab[2])
	{
		tab = get_key_name(tab[2]);
		if (tab[1])
			temp = ft_strjoin(tab[0], get_values(tab[1], env));
		else
			temp = ft_strjoin(tab[0], "");
		res = ft_strjoin(res, temp);
		free(temp);
	}
	printf("\033[31mget var return: %s\n\033[39m", res);
	return (res);
}


char	*replace_var_by_value(char *str, t_env_var **global, t_env_var **env)
{
	return (get_vars(str, env));
}

/* ---------------------------------------------------------------------------------*/

char	*get_last_unquoted(char *str)
{
	int	i;

	printf("str: %s (size: %ld)\n", str, ft_strlen(str));
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		printf("analyzing %s\n", &str[i]);
		if (str[i] == '\'' || str[i] == '"')
		{
			printf("get last unquoted %s\n", ft_strdup(&str[i + 1]));
			return (ft_strdup(&str[i + 1]));
		}
		i--;
	}
	return (0);
}

int	get_nb_quoted_words(char *str)
{
	int	i;
	int	j;
	int	nb;
	int	len;

	len = ft_strlen(str);
	nb = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (i > 0)
				nb++;
			j = i + 1;
			while (str[j] != '\0')
			{
				if (str[j] ==  str[i])
				{
					nb++;
					i = j + 1;
					break ;
				}
				j++;
			}
		}
		i++;
	}
	if (str[len - 1] != '\'' && str[len - 1] != '"')
		nb++;
	if (len > 0 && nb == 0)
		nb++;
	return (nb);
}

char	**fill_quoted_tab(char *str, int size)
{
	int	i;
	int	j;
	int	cell;
	char	**tab;
	int	last_alloc;

	last_alloc = -1;
	tab = malloc(sizeof(char *) * size);
	if (!tab)
		return (0);
	i = 0;
	while (i < size)
	{
		tab[i] = 0;
		i++;
	}
	cell = 0;
	if (str[0] != '"' && str[0] != '\'')
	{
		i = 0;
		while (str[i] != '\0' && str[i] != '\'' && str[i] != '"')
			i++;
		printf("\033[33mcase 1\033[39m\n");			// 1
		tab[0] = ft_strndup(str, i);
		cell = 1;
		last_alloc = i - 1;
	}
	else
		i = 0;
	while (str[i] != '\0')
	{
		printf("last_alloc: %d\n", last_alloc);
		printf("i:%d\n", i);
		if (str[i] == '\'' || str[i] == '"')
		{
			if (i != last_alloc + 1)
			{
				printf("\033[33m%d != %d\033[39m\n", i, last_alloc+1);
				printf("\033[33mallocated size: %d\033[39m\n", i - last_alloc);
				printf("\033[33mcase 2\033[39m\n");		//2
				tab[cell] = ft_strndup(&str[last_alloc + 1], i - last_alloc - 1);
				cell++;
				last_alloc = i;
			}
			printf("quote at %d\n", i);
			j = i + 1;
			while (str[j] != '\0')
			{
				if (str[j] == str[i])
				{
					printf("\033[33mcase 3 (malloc of size %d)\033[39m\n", j-i+1);		//3
					tab[cell] = ft_strndup(&str[i], j - i + 1);
					cell++;
					last_alloc = j;
					i = j; ///+ 1;
					break ;
				}
				j++;
			}
		}
		i++;
	}
	if (!tab[size - 1])
		tab[size - 1] = get_last_unquoted(str);
	return (tab);
}

char	*remove_quotes(char *str)
{
	int	len;
	int size;

	len = ft_strlen(str);
	if (str[len - 1] == '\'' || str[len - 1] == '"')
		size = len - 2;
	else
		size = len - 1;

	return (ft_strndup(&str[1], size));	
}

char	*join_tab(char **tab, int size)
{
	int	i;
	char	*res;
	//char	*temp;

	res = "";
	i = 0;
	while (i < size)
	{
		res = ft_strjoin(res, tab[i]);
		i++;
	}
	printf("jointab res: %s\n", res);
	return (res);
}

char	*get_quoted(char *str, t_env_var **env)
{
	int		size;
	char	**tab;
	
	size = get_nb_quoted_words(str);
	printf("there are %d tokens\n", size);
	tab = fill_quoted_tab(str, size);
	
	int i = 0;
	while (i < size)
	{
		printf("tab[%d]: %s\n", i, tab[i]);
		if (tab[i][0] != '\'')
			tab[i] = get_vars(tab[i], env);
		if (tab[i][0] == '\'' || tab[i][0] == '"')
			tab[i] = remove_quotes(tab[i]);
		printf("new tab[%d]: %s\n", i, tab[i]);
		i++;
	}
	return (join_tab(tab, size));
}

char	*simplify_quotes(char *str, t_env_var **env)
{
	return (get_quoted(str, env));
}

t_word	**var_expansion(t_word **words_lst, t_env_var **global_vars, t_env_var **env_vars)
{
	t_word	*current;
	int		quoted_case;

	if (!words_lst || !*words_lst)
		return (words_lst);
	current = *words_lst;
	while (current)
	{
		current->word = simplify_quotes(current->word, env_vars);
		// quoted_case = is_multiple_quoted(current->word);
		// if (quoted_case == 0)
		// {
		// 	if (is_quoted(current->word, '\''))
		// 	{
		// 		printf("\033[35m%s is single quoted\033[39m\n", current->word);
		// 		current->word = remove_quotes(current->word, '\'');
		// 	}
		// 	else if (is_quoted(current->word, '"'))
		// 	{
		// 		printf("\033[35m%s is double quoted\033[39m\n", current->word);
		// 		current->word = replace_var_by_value(current->word, global_vars, env_vars);
		// 		current->word = remove_quotes(current->word, '"');
		// 	}
		// 	else
		// 		current->word = replace_var_by_value(current->word, global_vars, env_vars);
				
		// }
		// else
		// {
		// 	if (quoted_case == 1)							// " '' "
		// 	{
		// 		current->word = remove_quotes(current->word, '"');
		// 		// Then need to handle ''
		// 	}
		// 	else if (quoted_case == 2)						// ' "" '
		// 		printf("\033[35mCase '\"\"'033[39m\n");
		// }
		current = current->next;
	}


	return (words_lst);
}