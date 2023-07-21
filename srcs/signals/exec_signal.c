/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:29:38 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/19 18:40:20 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

void	get_sig_event(int status)
{
	if (status == 2)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		g_status = 130;
	}
	if (status == 131)
	{
		printf("Quit (core dumped)\n");
		g_status = 131;
	}
}
