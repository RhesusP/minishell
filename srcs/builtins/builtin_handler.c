/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:15:00 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/22 14:51:48 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Execute the builtin command in the child process.
 * 
 * @param lst Command to execute.
 * @param env Environment variables list.
 * @param nb_pipes Number of pipes in the current command.
 * @return int 1 if the command is executed, 0 otherwise.
 */
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

/**
 * @brief Execute the builtin command without forking.
 * @details Export is executed in both parent and child process.
 * @param nb_pipes Number of pipes in the current command.
 * @return int 1 if the command is executed, 0 otherwise.
 */
int	execute_non_fork_builtin(int nb_pipes)
{
	t_word	*curr;

	curr = *(g_gbl.command);
	if (ft_strcmp(curr->word, "exit") == 0)
	{
		ft_exit(g_gbl);
		return (1);
	}
	else if (ft_strcmp(curr->word, "export") == 0)
	{
		ft_export(g_gbl.command, g_gbl.env, 0, nb_pipes);
		return (0);
	}
	else if (ft_strcmp(curr->word, "unset") == 0)
	{
		ft_unset(g_gbl.command, g_gbl.env);
		return (1);
	}
	else if (ft_strcmp(curr->word, "cd") == 0)
	{
		ft_cd(g_gbl.command, *(g_gbl.env));
		return (1);
	}
	return (0);
}
