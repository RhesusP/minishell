/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:23:47 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/13 16:03:20 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

t_env_var	*get_old_pwd(t_env_var *env)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "OLDPWD") == 0)
			return (current);
		current = current->next;
	}
	return (0);
}

t_env_var	*get_pwd(t_env_var *env)
{
	t_env_var	*current;

	if (!env)
		return (0);
	current = env;
	while (current && ft_strcmp(current->key, "PWD") != 0)
		current = current->next;
	return (current);
}

int	is_abs_path(char *path)
{
	if (path[0] == '/')
		return (1);
	return (0);
}

char	*get_valid_pwd(char *pwd, char *input)
{
	char	*path;
	char	*tmp;

	if (is_abs_path(input))
		return (ft_strdup(input));
	if (ft_strlen(ft_strrchr(pwd, '/')) == 1)	// si l'ancien pwd se termine par /
		return (ft_strjoin(pwd, input));
	tmp = ft_strjoin(pwd, "/");
	path = ft_strjoin(tmp, input);
	free(tmp);
	return (path);
}

void	change_pwd(t_env_var *env, char *new_pwd)
{
	t_env_var	*pwd;
	t_env_var	*old_pwd;
	
	old_pwd = get_old_pwd(env);
	pwd = get_pwd(env);
	old_pwd->values[0] = ft_strdup(pwd->values[0]);
	pwd->values[0] = get_valid_pwd(old_pwd->values[0], new_pwd);
	if (chdir(new_pwd) != 0)
		perror(new_pwd);
}

void	go_back_in_pwd(t_env_var *env)
{
	t_env_var	*pwd;
	t_env_var	*old_pwd;
	char		**tab;
	char		*res;
	char		*tmp;
	int			i;
	int			size;

	old_pwd = get_old_pwd(env);
	pwd = get_pwd(env);
	old_pwd->values[0] = ft_strdup(pwd->values[0]);
	tab = ft_split(old_pwd->values[0], '/');
	size = 0;
	while (tab[size])
		size++;
	i = 0;
	res = "/";
	while (i < size - 1)
	{
		res = ft_strjoin(res, tab[i]);
		res = ft_strjoin(res, "/");
		i++;
	}
	pwd->values[0] = res;
	if (chdir(res) != 0)
		perror(res);
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
	if (nb_arg == 0 || (nb_arg == 1 && ft_strcmp(path->word, "~") == 0))
		change_pwd(env, get_home(env));
	else if (nb_arg == 1 && ft_strcmp(path->word, ".") == 0)
	 	return ;
	else if (nb_arg == 1 && ft_strcmp(path->word, "..") == 0)
		go_back_in_pwd(env);
	else if (nb_arg == 1)
		change_pwd(env, path->word);
	else
		perror("Too many arguments");	// wtf ?
}