/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:01:10 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/18 22:59:13 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*get_temp_path(char *str)
{
	char	*pwd;
	char	*temp1;
	char	*temp;

	if (str[0] != '/')
	{
		pwd = ft_getcwd();
		temp1 = ft_strjoin(pwd, "/");
		temp = ft_strjoin(temp1, str);
		free(temp1);
		free(pwd);
	}
	else
		temp = ft_strdup(str);
	return (temp);
}

void	simplify_path(char *str, t_env_var *env)
{
	char	*temp;
	char	**tab;
	char	*path;

	if (str[0] == '-' && ft_strlen(str) == 1)
	{
		switch_old_curr_pwd(env);
		return ;
	}
	temp = get_temp_path(str);
	tab = create_dir_tab(temp, count_dir(temp));
	path = recreate_new_path(tab, count_dir(temp));
	free(temp);
	change_pwd(env, path, 1);
	if (path)
		free(path);
	free_all(tab);
}
