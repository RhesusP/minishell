/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:26:17 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/13 10:15:41 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
	else if (sig == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

/**
 * @brief Handle Ctrl-D "signal"
 * 
 * @param line User input. 
 */
void	handle_ctrld(char *line, t_env_var *env, t_env_var *global)
{
	if (!line)
	{
		printf("exit\n");
		ft_free(env, global);
		exit(g_status);
	}
}

/**
 * @brief Signal handler for SIGINT (Ctrl-C) and SIGQUIT (Ctrl-\)
 * 
 */
void	signal_handler(void)
{
	struct sigaction	act;

	act.sa_handler = sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}
