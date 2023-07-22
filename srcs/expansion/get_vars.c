/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:28:59 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:35:01 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

/**
 * @brief Free the tab of strings.
 * @details Free the tab with the following cells : 
 * 0 : string before the key name.
 * 1 : key name.
 * 2 : string after the key name.
 * @param tab Tab to free.
 */
static void	free_var_tab(char **tab)
{
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
}

static char	**first_extract(char *str, t_env_var **e, char **res)
{
	char	**tab;
	char	*temp;

	tab = get_key_name(str);
	temp = get_values(tab[1], e);
	*res = ft_strjoin_nullable(tab[0], temp);
	free(temp);
	return (tab);
}

static void	get_remains(char **r, char ***tab, char **res, t_env_var **env)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	*tab = get_key_name(*r);
	free(*r);
	if ((*tab)[2])
		*r = ft_strdup((*tab)[2]);
	else
		*r = 0;
	temp2 = get_values((*tab)[1], env);
	temp = ft_strjoin_nullable((*tab)[0], temp2);
	free(temp2);
	temp1 = ft_strdup(*res);
	free(*res);
	*res = ft_strjoin_nullable(temp1, temp);
	free(temp);
	free(temp1);
	free_var_tab(*tab);
}

/**
 * @brief Expand the variables in a string.
 * 
 * @param str String to expand.
 * @param env Environment variables.
 * @return char* The expanded string.
 */
char	*get_vars(char *str, t_env_var **env)
{
	char		**tab;
	char		*res;
	char		*remains;

	remains = 0;
	if (ft_strlen(str) == 1 && str[0] == '$')
		return (str);
	tab = first_extract(str, env, &res);
	if (tab[2])
		remains = ft_strdup(tab[2]);
	free_var_tab(tab);
	while (remains)
		get_remains(&remains, &tab, &res, env);
	free(str);
	return (res);
}
