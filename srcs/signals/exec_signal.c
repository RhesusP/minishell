/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svanmeen <svanmeen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:29:38 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/23 09:38:18 by svanmeen         ###   ########.fr       */
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
		g_gbl.status = 130;
	}
	if (status == 131)
	{
		write(1, "", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\rQuit (core dumped)\n");
		g_gbl.status = 131;
	}
}
