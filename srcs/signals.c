/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:26:17 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/19 13:57:29 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	restore_prompt(int sig)
{
	(void)sig;
	rl_on_new_line();
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 130;
}

void	ctrl_c(int sig)
{
	g_status = 130;
	write(1, "\n", 1);
	(void)sig;
	exit(g_status);
}

/// @brief Handle [Ctrl + \ ] 'signal'
/// @param sig SIGQUIT
void	back_slash(int sig)
{
	g_status = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
	exit(g_status);
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
void	handle_ctrld(char *line, t_env_var *env, t_env_var *global)
{
	if (!line)
	{
		printf("exit\n");
		ft_free(env, global);
		exit(g_status);
	}
}
