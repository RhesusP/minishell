/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 10:42:25 by tbarde-c           #+#    #+#             */
/*   Updated: 2023/02/22 12:02:18 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
		printf("\n$> ");
	else if (sig == SIGQUIT)
		printf("\33[2K\r$> ");
}

/**
 * @brief Handle Ctrl-D "signal" - Free everything we have to
 * 
 * @param line User input. 
 */
void	handle_ctrld(char *line, t_env_var *env_var, t_env_var *global_var)
{
	if (!line)
	{
		free_env_var(env_var);
		free_env_var(global_var);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

/**
 * @brief Signal handler for SIGINT (Ctrl-C) and SIGQUIT (Ctrl-\)
 * 
 */
void	signal_handler(void)
{
	struct sigaction	act;

	act.sa_handler = &sig_handler;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}