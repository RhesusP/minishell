/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmeen <svanmeen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:28:59 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/12 13:57:44 by svanmeen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static void	free_var_tab(char **tab)
{
	free(tab[0]);
	free(tab[1]);
	free(tab[2]);
	free(tab);
}

static char	**first_extract(char *str, t_env_var **e, t_env_var **g, char **res)
{
	char	**tab;
	char	*temp;

	tab = get_key_name(str);
	temp = get_values(tab[1], e, g);
	*res = ft_strjoin_nullable(tab[0], temp);
	free(temp);
	return (tab);
}

static void	get_remains(char **r, char ***tab, char **res, t_to_free envs)
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
	temp2 = get_values((*tab)[1], envs.env, envs.global);
	temp = ft_strjoin_nullable((*tab)[0], temp2);
	free(temp2);
	temp1 = ft_strdup(*res);
	free(*res);
	*res = ft_strjoin_nullable(temp1, temp);
	free(temp);
	free(temp1);
	free_var_tab(*tab);
}

char	*get_vars(char *str, t_env_var **env, t_env_var **global)
{
	char		**tab;
	char		*res;
	char		*remains;
	t_to_free	envs;

	envs.env = env;
	envs.global = global;
	remains = 0;
	if (ft_strlen(str) == 1 && str[0] == '$')
		return (str);
	tab = first_extract(str, env, global, &res);
	if (tab[2])
		remains = ft_strdup(tab[2]);
	free_var_tab(tab);
	while (remains)
		get_remains(&remains, &tab, &res, envs);
	free(str);
	return (res);
}
