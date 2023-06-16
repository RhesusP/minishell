/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:21:08 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:36:06 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static void	free_tab(char **tab)
{
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
}

static char	*get_rest(char *s, t_env_var **e, t_env_var **g, char **rem)
{
	char	**tab;
	char	*temp;
	char	*res;

	tab = get_key_name(s);
	temp = get_values(tab[1], e, g);
	res = ft_strjoin_nullable(tab[0], temp);
	free(temp);
	if (tab[2])
		*rem = ft_strdup(tab[2]);
	else
		*rem = 0;
	free_tab(tab);
	return (res);
}

static void	extract_val(char **rem, t_env_var **e, t_env_var **g, char **res)
{
	char	**tab;
	char	*temp;
	char	*temp1;
	char	*temp2;

	tab = get_key_name(*rem);
	free(*rem);
	*rem = tab[2];
	temp2 = get_values(tab[1], e, g);
	temp = ft_strjoin_nullable(tab[0], temp2);
	free(temp2);
	temp1 = ft_strdup(*res);
	free(*res);
	*res = ft_strjoin_nullable(temp1, temp);
	free(temp);
	free(temp1);
	free_tab(tab);
}

char	*get_vars(char *str, t_env_var **env, t_env_var **global)
{
	char	*res;	
	char	*remains;

	if (ft_strlen(str) == 1 && str[0] == '$')
		return (str);
	res = get_rest(str, env, global, &remains);
	while (remains)
		extract_val(&remains, env, global, &res);
	free(str);
	return (res);
}
