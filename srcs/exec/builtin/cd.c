/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:23:47 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/11 18:12:27 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
// #include "../../../includes/exec.h"

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
	// tab[0] = ft_strdup("/");
	cell = 0;
	i = 0;
	while (str[i] != '\0')
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
	// i = 0;
	// while (tab[i])
	// {
	// 	printf("tab[%d]: %s\n", i, tab[i]);
	// 	i++;
	// }
	return (tab);
}

char	*recreate_new_path(char **tab, int size)
{
	int	i;
	int	j;
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
	
	if (!tab[0])
		res = "/";
	else
		res = "";
	i = 0;
	while (i < size)
	{
		if (tab[i])
		{
			temp = ft_strjoin("/", tab[i]);
			res = ft_strjoin(res, temp);
		}
		i++;
	}
	return (res);
}

void	change_directory(char *path, t_env_var *env)
{
	t_env_var	*old_pwd;
	t_env_var	*pwd;

	printf("change directory to %s\n", path);
	if (chdir(path) != 0)
	{
		perror(path);
		return ;
	}
	old_pwd = get_old_pwd(env);
	pwd = get_pwd(env);
	old_pwd->values[0] = pwd->values[0];
	pwd->values[0] = path;
}

void	switch_old_curr_pwd(t_env_var *env)
{
	t_env_var	*old_pwd;
	t_env_var	*pwd;
	char		*temp;
	char		*path;

	old_pwd = get_old_pwd(env);
	if (!old_pwd)
	{
		ft_putendl_fd("cd: OLDPWD not set", 2);
		g_status = 1;
		return ;
	}
	if (chdir(old_pwd->values[0]) != 0)
	{
		perror(old_pwd->values[0]);
		return ;
	}
	pwd = get_pwd(env);
	temp = old_pwd->values[0];
	old_pwd->values[0] = pwd->values[0];
	pwd->values[0] = temp;
}

void	simplify_path(char *str, t_env_var *env)
{
	char	*res;
	char	*temp;
	char	**tab;
	char	*path;

	if (str[0] == '-' && ft_strlen(str) == 1)
	{
		switch_old_curr_pwd(env);
		return ;
	}
	if (str[0] != '/')
	{
		temp = ft_strjoin(get_pwd(env)->values[0], "/");
		temp = ft_strjoin(temp, str);
	}
	else
		temp = ft_strdup(str);
	printf("abs path is %s\n", temp);
	printf("there are %d directories\n", count_dir(temp));
	tab = create_dir_tab(temp, count_dir(temp));
	path = recreate_new_path(tab, count_dir(temp));
	printf("here HERE\n");
	change_directory(path, env);
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
		change_pwd(env, get_home(env));
	else if (nb_arg == 1)
		simplify_path(path->word, env);
	else
		ft_putendl_fd("cd: too many arguments", 2);
}