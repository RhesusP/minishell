/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:29:38 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 12:06:17 by cbernot          ###   ########.fr       */
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
		printf("Quit (core dumped)\n");
		g_gbl.status = 131;
	}
}
