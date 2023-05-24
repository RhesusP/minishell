/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:37:25 by cbernot           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/17 12:51:25 by cbernot          ###   ########.fr       */
=======
/*   Updated: 2023/05/21 16:09:42 by cbernot          ###   ########.fr       */
>>>>>>> 5731c5c34bec1129cc1f9ba4101635e78d5b9624
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	**get_key_name(char *str)
{
	int		len;
	int		i;
	char	**tab;

	// printf("\033[31mget key name start with: %s\n\033[39m", str);
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

// char	*values_to_str(char **tab)
// {
// 	char	*res;
// 	char	*temp;
// 	int		i;

// 	temp = "";
// 	res = 0;
// 	if (!tab)
// 		return (0);
// 	i = 0;
// 	while (tab[i])
// 	{
// 		if (i > 0)
// 			temp = ft_strdup(res);
// 		if (res)
// 			free(res);
// 		res = ft_strjoin(temp, tab[i]);
// 		if (i > 0)
// 			free(temp);
// 		i++;
// 	}
// 	return (res);
// }

char	*values_to_str(char **tab)
{
	int		i;
	char	*res;
	char	*temp;

	i = 0;
	res = malloc(sizeof(char));
	res[0] = '\0';
	if (!tab)
		return (res);
	while (tab[i])
	{
		temp = ft_strjoin_nullable(res, tab[i]);
		free(res);
		res = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (res);
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
	{
		printf("key is a dollar symbol\n");
		return (ft_strdup("$"));
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

char	*get_vars(char *str, t_env_var **env, t_env_var **global)
{
	char	**tab;
	char	**temp_tab;
	char	*res;
	char	*temp;
	char	*temp1;
	char	*temp2;
	char	*remains;

	if (ft_strlen(str) == 1 && str[0] == '$')
		return (str);
	tab = get_key_name(str);
	// printf("before: %s\n", tab[0]);
	// printf("key: %s\n", tab[1]);
	// printf("after: %s\n", tab[2]);


	temp2 = get_values(tab[1], env, global);
	res = ft_strjoin_nullable(tab[0], temp2);
	free(temp2);
	if (tab[2])
		remains = ft_strdup(tab[2]);
	else
		remains = 0;
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
	while(remains)
	{
		tab = get_key_name(remains);
		free(remains);
		remains = tab[2];
		temp2 = get_values(tab[1], env, global);
		temp = ft_strjoin_nullable(tab[0], temp2);
		free(temp2);
		temp1 = ft_strdup(res);
		free(res);
		res = ft_strjoin_nullable(temp1, temp);
		free(temp);
		free(temp1);
		free(tab[0]);
		free(tab[1]);
		free(tab[2]);
		free(tab);
	}
	free(str);
	// printf("\033[31mget var return: %s\n\033[39m", res);
	return (res);
}

/* ---------------------------------------------------------------------------------*/

char	*get_last_unquoted(char *str)
{
	int	i;

	// printf("str: %s (size: %ld)\n", str, ft_strlen(str));
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		// printf("analyzing %s\n", &str[i]);
		if (str[i] == '\'' || str[i] == '"')
		{
			// printf("get last unquoted %s\n", ft_strdup(&str[i + 1]));
			return (ft_strdup(&str[i + 1]));
		}
		i--;
	}
	return (0);
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
	tab = malloc(sizeof(char *) * (size + 1));		// TODO check if +1 causes leaks
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
		// printf("\033[33mcase 1\033[39m\n");			// 1
		tab[0] = ft_strndup(str, i);
		cell = 1;
		last_alloc = i - 1;
	}
	else
		i = 0;
	while (str[i] != '\0')
	{
		// printf("last_alloc: %d\n", last_alloc);
		// printf("i:%d\n", i);
		if (str[i] == '\'' || str[i] == '"')
		{
			if (i != last_alloc + 1)
			{
				// printf("\033[33m%d != %d\033[39m\n", i, last_alloc+1);
				// printf("\033[33mallocated size: %d\033[39m\n", i - last_alloc);
				// printf("\033[33mcase 2\033[39m\n");		//2
				tab[cell] = ft_strndup(&str[last_alloc + 1], i - last_alloc - 1);
				cell++;
				last_alloc = i;
			}
			// printf("quote at %d\n", i);
			j = i + 1;
			while (str[j] != '\0')
			{
				if (str[j] == str[i])
				{
					// printf("\033[33mcase 3 (malloc of size %d)\033[39m\n", j-i+1);		//3
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
	{
		// printf("\033[33mcase 4 (get last unquoted)\033[39m\n");		//4
		tab[size - 1] = get_last_unquoted(str);
	}
	tab[size] = 0;
	// int z = 0;
	// while (z < size)
	// {
		// printf("returning tab: %s\n", tab[z]);
		// z++;
	// }
	return (tab);
}

char	*remove_quotes(char *str)
{
	int	len;
	int size;

	len = ft_strlen(str);
	// printf("len: %d\nstr: %s\n", len, str);
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
	char	*temp;

	res = 0;
	i = 0;
	while (i < size)
	{
		temp = ft_strjoin_nullable(res, tab[i]);
		if (res)
			free(res);
		res = ft_strdup(temp);
		free(temp);
		i++;
	}
	return (res);
}












char	*get_quoted(char *str, t_env_var **env, t_env_var **global)
{
	int		size;
	char	**tab;
	char	*res;
	char	*temp;
	
	size = get_nb_quoted_words(str);
	// printf("there are %d tokens\n", size);
	// printf("size: %d\n", size);


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
		// printf("new tab[%d]: %s\n", i, tab[i]);
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
		// printf("-----------------\n");
		// ok
		temp = get_quoted(current->word, env_vars, global_vars);		//if error, check here first
		free(current->word);
		current->word = temp;
		current = current->next;
	}
}