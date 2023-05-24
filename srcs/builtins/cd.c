/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:23:47 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/20 22:10:46 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") != 0)
			return (current);
		current = current->next;
	}
	return (0);
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

void	change_pwd(t_env_var *env, char *new_pwd, int to_free)
{
	t_env_var	*pwd;
	t_env_var	*old_pwd;
	char		*temp;

	if (chdir(new_pwd) != 0)
	{
		g_status = 1;
		perror(new_pwd);
		free(new_pwd);
		return ;
	}
	old_pwd = get_old_pwd(env);
	pwd = get_pwd(env);
	if (!old_pwd)
		add_back_env_var(&env, create_env_var(ft_strjoin("OLDPWD=", ft_getcwd())));
	else
	{
		free(old_pwd->values);
		temp = ft_getcwd();
		old_pwd->values = malloc(sizeof(char *) * 2);
		old_pwd->values[0] = ft_strdup(temp);
		old_pwd->values[1] = 0;
		free(temp);
		// free(old_pwd->values[0]);
		// old_pwd->values[0] = ft_getcwd();
	}
	if (!pwd)
	{
		temp = ft_strjoin("PWD=", new_pwd);
		add_back_env_var(&env, create_env_var(temp));
		free(temp);
	}
	else
	{
		free(pwd->values[0]);
		pwd->values[0] = new_pwd;
	}
	g_status = 0;
}

int	count_dir(char *path)
{
	int	i;
	int	reset;
	int	nb;

	reset = 1;
	nb = 0;
	i = 0;
	while (path[i] != '\0')
	{
		if (path[i] != '/' && reset)
		{
			nb++;
			reset = 0;
		}
		else if (path[i] == '/')
			reset = 1;
		i++;
	}
	return (nb);
}

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
	while (i < ft_strlen(str) && str[i] != '\0')
	{
		j = i;
		while(str[j] != '/' && str[j] != '\0')
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

char	*recreate_new_path(char **tab, int size)
{
	int		i;
	int		j;
	char	*res;
	char	*temp;

	i = 0;
	while (tab[i] && i < size)
	{
		if (tab[i] && ft_strcmp(tab[i], ".") == 0)
		{
			free(tab[i]);
			tab[i] = 0;
		}
		else if (tab[i] && ft_strcmp(tab[i], "..") == 0)
		{
			j = i - 1;
			while (!tab[j])
				j--;
			if (j >= 0)
			{
				free(tab[j]);
				tab[j] = 0;
			}
			free(tab[i]);
			tab[i] = 0;
		}
		i++;
	}
	char	*temp1;
	res = 0;
	if (!tab[0])
		res = ft_strdup("/");
	i = 0;
	while (i < size)
	{
		if (tab[i])
		{
			temp = ft_strjoin("/", tab[i]);
			temp1 = ft_strjoin_nullable(res, temp);
			free(res);
			free(temp);
			res = ft_strdup(temp1);
			free(temp1);
		}
		i++;
	}
	return (res);
}

// void	switch_old_curr_pwd(t_env_var *env)
// {
// 	t_env_var	*old_pwd;
// 	t_env_var	*pwd;
// 	char		*temp;
// 	char		*env_line;

// 	old_pwd = get_old_pwd(env);
// 	if (!old_pwd)
// 	{
// 		ft_putendl_fd("cd: OLDPWD not set", 2);
// 		g_status = 1;
// 		return ;
// 	}
// 	temp = ft_getcwd();
// 	if (chdir(old_pwd->values[0]) != 0)
// 	{
// 		perror(old_pwd->values[0]);
// 		g_status = 1;
// 		free(temp);
// 		return ;
// 	}
// 	pwd = get_pwd(env);
// 	if (!pwd)
// 	{
// 		env_line = ft_strjoin("PWD=", old_pwd->values[0]);
// 		add_back_env_var(&env, create_env_var(env_line));
// 		free(env_line);
// 	}
// 	old_pwd->values[0] = temp;
// 	g_status = 0;
// }

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
	change_pwd(env, old_pwd->values[0], 1);
}

void	simplify_path(char *str, t_env_var *env)
{
	char	*temp;
	char	**tab;
	char	*path;
	char	*pwd;
	char	*temp1;

	if (str[0] == '-' && ft_strlen(str) == 1)
	{
		switch_old_curr_pwd(env);
		return ;
	}
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
	tab = create_dir_tab(temp, count_dir(temp));
	path = recreate_new_path(tab, count_dir(temp));
	free(temp);
	change_pwd(env, path, 1);
	int	i;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
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
	{
		char *home = get_home(env);
		if (!home)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			g_status = 1;
			return ;
		}
		else
			change_pwd(env, home, 1);
	}
	else if (nb_arg == 1)
		simplify_path(path->word, env);
	else
	{
		ft_putendl_fd("cd: too many arguments", 2);
		g_status = 1;
	}
}