/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:26:17 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 13:43:11 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	restore_prompt(int sig)
{
	(void)sig;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_gbl.status = 130;
}

void	ctrl_c(int sig)
{
	g_gbl.status = 130;
	write(1, "\n", 1);
	(void)sig;
	if (g_gbl.in_hd)
	{
		free_redir(g_gbl.redir);
		g_gbl.redir = 0;
		free_all(g_gbl.full_cmd);
		g_gbl.full_cmd = 0;
		free_and_exit(&g_gbl, 1, g_gbl.status, 1);
	}
	exit(g_gbl.status);
}

/// @brief Handle [Ctrl + \ ] 'signal'
/// @param sig SIGQUIT
void	back_slash(int sig)
{
	g_gbl.status = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
	if (g_gbl.in_hd)
	{
		free_redir(g_gbl.redir);
		g_gbl.redir = 0;
		free_all(g_gbl.full_cmd);
		g_gbl.full_cmd = 0;
		free_and_exit(&g_gbl, 1, g_gbl.status, 1);
	}
	exit(g_gbl.status);
}

void	signal_handler(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
}

/**
 * @brief Handle Ctrl-D "signal"
 * 
 * @param line User input. 
 */
void	handle_ctrld(char *line, t_env_var *env)
{
	if (!line)
	{
		printf("exit\n");
		ft_free(env);
		exit(g_gbl.status);
	}
}
