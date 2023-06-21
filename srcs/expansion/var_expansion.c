/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:37:25 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/21 17:29:27 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

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
		
	if (i > 0)
		tab[0] = ft_strndup(str, i);
	else
		tab[0] = 0;
	len = i;
	len += 1;
	if (len < ft_strlen(str))
	{
		while (str[len] != '\0' && (str[len] == '_' || str[len] == '?' || ft_isalnum(str[len])))
			len++;
		tab[1] = ft_strndup(&str[i], len - i);
		if (len < ft_strlen(str) && str[len])
			tab[2] = ft_strdup(&str[len]);
		else
			tab[2] = 0;
	}
	else
	{
		tab[1] = 0;
		tab[2] = 0;
	}
	return (tab);
}

char	*get_values(char *key, t_env_var **lst, t_env_var **global)
{
	t_env_var	*current;
	char		**values;
	int			stop;

	stop = 0;
	values = 0;
	
	if (!*lst || !key)
		return (0);
	if (ft_strcmp(key, "$") == 0)
		return (ft_strdup("$"));
	else if (ft_strcmp(key, "$?") == 0)
		return (ft_itoa(g_status));
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
	if (!values && *global)
	{
		stop = 0;
		current = *global;
		while (current && !stop)
		{
			if (ft_strcmp(current->key, key) == 0)
			{
				values = current->values;
				stop = 1;
			}
			current = current->next;
		}
	}
	return (values_to_str(values));
}

int    get_nb_quoted_words(char *str)
{
    int    i;
    int    j;
    int    nb;
    int    len;
    int    unquoted;

    unquoted = 0;
    len = ft_strlen(str);
    nb = 0;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            if (unquoted)
                nb++;
            unquoted = 0;
            j = i + 1;
            while (str[j] != '\0')
            {
                if (str[j] ==  str[i])
                {
                    nb++;
                    i = j;
                    break ;
                }
                j++;
            }
        }
        else
          unquoted = 1;   
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
	int		i;
	int		j;
	int		cell;
	char	**tab;
	int		last_alloc;

	last_alloc = -1;
	tab = malloc(sizeof(char *) * (size + 1));
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
		tab[0] = ft_strndup(str, i);
		cell = 1;
		last_alloc = i - 1;
	}
	else
		i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (i != last_alloc + 1)
			{
				tab[cell] = ft_strndup(&str[last_alloc + 1], i - last_alloc - 1);
				cell++;
				last_alloc = i;
			}
			j = i + 1;
			while (str[j] != '\0')
			{
				if (str[j] == str[i])
				{
					tab[cell] = ft_strndup(&str[i], j - i + 1);
					cell++;
					last_alloc = j;
					i = j;
					break ;
				}
				j++;
			}
		}
		i++;
	}
	if (!tab[size - 1])
		tab[size - 1] = get_last_unquoted(str);
	tab[size] = 0;
	return (tab);
}

char	*get_quoted(char *str, t_env_var **env, t_env_var **global)
{
	int		size;
	char	**tab;
	char	*res;
	char	*temp;
	
	size = get_nb_quoted_words(str);
	tab = fill_quoted_tab(str, size);
	int i = 0;
	while (i < size)
	{
		if (tab[i][0] != '\'')
			tab[i] = get_vars(tab[i], env, global);
		if (tab[i][0] == '\'' || tab[i][0] == '"')
		{
			temp = remove_quotes(tab[i]);
			free(tab[i]);
			tab[i] = temp;
		}
		i++;
	}
	res = join_tab(tab, size);
	i = 0;	
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (res);
}

void	var_expansion(t_word **words_lst, t_env_var **global_vars, t_env_var **env_vars)
{
	t_word	*current;
	int		quoted_case;
	char	*temp;

	if (!words_lst || !*words_lst)
		return ;
	current = *words_lst;
	while (current)
	{
		temp = get_quoted(current->word, env_vars, global_vars);
		free(current->word);
		current->word = temp;
		current = current->next;
	}
}
