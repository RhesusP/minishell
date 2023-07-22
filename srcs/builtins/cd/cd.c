/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 11:40:28 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:54:02 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * @brief Convert a path in a string array where each cell is a directory.
 * @details Example: "/home/user" -> ["/", "home", "user"].
 * @param str Path to convert.
 * @param nb_dir Number of directories in the path.
 * @return char** String array where each cell is a directory.
 */
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

/**
 * @brief Switch the current directory to the previous one.
 * 
 * @param env 
 */
void	switch_old_curr_pwd(t_env_var *env)
{
	t_env_var	*old_pwd;

	old_pwd = get_old_pwd(env);
	if (!old_pwd || !old_pwd->values || !old_pwd->values[0])
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		g_gbl.status = 1;
		return ;
	}
	change_pwd(env, old_pwd->values[0]);
}

/**
 * @brief Change the current directory to the home directory.
 * 
 * @param env 
 */
static void	go_home(t_env_var *env)
{
	char	*home;

	home = get_home(env);
	if (!home)
	{
		ft_putendl_fd("cd: HOME not set", 2);
		g_gbl.status = 1;
	}
	else
		change_pwd(env, home);
}

/**
 * @brief Change the current directory.
 * @details If the path is relative, it will be simplified, if there is no
 * directory, it will go to the home directory.
 * @param lst Curent command.
 * @param env Environment variables list.
 */
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
		g_gbl.status = 1;
	}
}
