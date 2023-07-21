/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:15:00 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 11:44:41 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_word **lst, t_env_var **env, int nb_pipes)
{
	t_word	*curr;

	curr = *lst;
	if (ft_strcmp(curr->word, "export") == 0)
	{
		ft_export(lst, env, 1, nb_pipes);
		return (1);
	}
	else if (ft_strcmp(curr->word, "pwd") == 0)
	{
		ft_pwd();
		return (1);
	}
	else if (ft_strcmp(curr->word, "echo") == 0)
	{
		ft_echo(lst);
		return (1);
	}
	else if (ft_strcmp(curr->word, "env") == 0)
	{
		ft_env(lst, *env);
		return (1);
	}
	return (0);
}

int	execute_non_fork_builtin(t_to_free to_free, int nb_pipes)
{
	t_word	*curr;

	curr = *(to_free.command);
	if (ft_strcmp(curr->word, "exit") == 0)
	{
		ft_exit(to_free);
		return (1);
	}
	else if (ft_strcmp(curr->word, "export") == 0)
	{
		ft_export(to_free.command, to_free.env, 0, nb_pipes);
		return (0);
	}
	else if (ft_strcmp(curr->word, "unset") == 0)
	{
		ft_unset(to_free.command, to_free.env);
		return (1);
	}
	else if (ft_strcmp(curr->word, "cd") == 0)
	{
		ft_cd(to_free.command, *(to_free.env));
		return (1);
	}
	return (0);
}
