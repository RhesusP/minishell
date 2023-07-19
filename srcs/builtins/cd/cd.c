/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:40:28 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/19 09:11:48 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**create_dir_tab(char *str, int nb_dir)
{
	char	**tab;
	int		i;
	int		j;
	int		cell;

	tab = malloc(sizeof(char *) * (nb_dir + 1));
	if (!tab)
		return (0);
	cell = 0;
	i = 0;
	while (i < (int)ft_strlen(str) && str[i] != '\0')
	{
		j = i;
		while (str[j] != '/' && str[j] != '\0')
			j++;
		if (j != i)
		{
			tab[cell] = ft_strndup(&str[i], j - i);
			cell++;
		}
		i = j + 1;
	}
	tab[nb_dir] = 0;
	return (tab);
}

void	switch_old_curr_pwd(t_env_var *env)
{
	t_env_var	*old_pwd;

	old_pwd = get_old_pwd(env);
	if (!old_pwd || !old_pwd->values || !old_pwd->values[0])
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		g_status = 1;
		return ;
	}
	change_pwd(env, old_pwd->values[0]);
}

static void	go_home(t_env_var *env)
{
	char	*home;

	home = get_home(env);
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		g_status = 1;
	}
	else
		change_pwd(env, home);
}

void	ft_cd(t_word **lst, t_env_var *env)
{
	t_word	*current;
	t_word	*path;
	int		nb_arg;

	nb_arg = 0;
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		nb_arg++;
		path = current;
		current = current->next;
	}
	if (nb_arg == 0)
		go_home(env);
	else if (nb_arg == 1)
		simplify_path(path->word, env);
	else
	{
		ft_putendl_fd("cd: too many arguments", 2);
		g_status = 1;
	}
}
