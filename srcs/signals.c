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
		printf("\n\033[1;36mminishell $>\033[00m ");
	else if (sig == SIGQUIT)
		printf("\33[2K\r\033[1;36mminishell $>\033[00m ");
}

/**
 * @brief Handle Ctrl-D "signal"
 * 
 * @param line User input. 
 */
void	handle_ctrld(char *line)
{
	if (!line)
	{
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