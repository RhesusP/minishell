/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:37:25 by cbernot           #+#    #+#             */
/*   Updated: 2023/04/25 19:28:13 by cbernot          ###   ########.fr       */
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

char	*remove_quotes(char *str, char quote)
{
	int	len_before;
	int	len_between;
	char	*bef;
	char	*bet;
	char	*aft;
	char 	*res;
	char	*temp;

	len_before = 0;
	while (str[len_before] != '\0' && str[len_before] != quote)
		len_before++;
	bef = ft_strndup(str, len_before);
	len_between = len_before + 1;
	while (str[len_between] != '\0' && str[len_between] != quote)
		len_between++;
	bet = ft_strndup(&str[len_before + 1], len_between - 1 - len_before);
	aft = ft_strdup(&str[len_between + 1]);
	temp = ft_strjoin(bef, bet);
	res = ft_strjoin(temp, aft);
	printf("bef: %s\n", bef);
	printf("bet: %s\n", bet);
	printf("aft: %s\n", aft);
	free(temp);
	free(bef);
	free(bet);
	free(aft);
	free(str);
	return (res);
}

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

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '$')
		i++;
	tab[0] = ft_strndup(str, i);
	len = i;
	len += 1;
	while (str[len] != '\0' && ft_isalnum(str[len]))
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
	return (res);
}


char	*replace_var_by_value(char *str, t_env_var **global, t_env_var **env)
{
	return (get_vars(str, env));
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
		quoted_case = is_multiple_quoted(current->word);
		if (quoted_case == 0)
		{
			if (is_quoted(current->word, '\''))
			{
				printf("\033[35m%s is single quoted\033[39m\n", current->word);
				current->word = remove_quotes(current->word, '\'');
			}
			else if (is_quoted(current->word, '"'))
			{
				printf("\033[35m%s is double quoted\033[39m\n", current->word);
				current->word = replace_var_by_value(current->word, global_vars, env_vars);
				current->word = remove_quotes(current->word, '"');
			}
			else
				current->word = replace_var_by_value(current->word, global_vars, env_vars);
				
		}
		else
		{
			if (quoted_case == 1)							// " '' "
			{
				current->word = remove_quotes(current->word, '"');
				// Then need to handle ''
			}
			else if (quoted_case == 2)						// ' "" '
				printf("\033[35mCase '\"\"'033[39m\n");
		}


		
		// if (ft_strchr(current->word, '$'))
		// {
		// 	printf("variable detected\n");
		// }
		current = current->next;
	}


	return (words_lst);
}