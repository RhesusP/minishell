/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:02:12 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 13:41:30 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit(t_to_free *f, int is_exit, int exit_status, int u)
{
	if (u)
		unlink_he_files(f, f->nb_pipes);
	free(g_gbl.pids);
	ft_free(*(g_gbl.env));
	free(g_gbl.line);
	free_word_lst(g_gbl.lst);
	free_word_lst(g_gbl.command);
	if (is_exit)
		exit(exit_status);
}

static void	init_pids_tab(int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes + 1)
	{
		g_gbl.pids[i] = 0;
		i++;
	}
}

void	init_to_free(int nb_pipes, t_word **word, char *line)
{
	int	i;

	g_gbl.pids = malloc(sizeof(int) * (nb_pipes + 1));
	if (!g_gbl.pids)
		return ;
	init_pids_tab(nb_pipes);
	g_gbl.he_files = malloc(sizeof(char *) * (nb_pipes + 2));
	if (!g_gbl.he_files)
		return ;
	i = 0;
	while (i < nb_pipes + 2)
	{
		g_gbl.he_files[i] = 0;
		i++;
	}
	g_gbl.lst = word;
	g_gbl.line = line;
	g_gbl.command = malloc(sizeof(t_word *));
	if (!g_gbl.command)
		return ;
	*(g_gbl.command) = 0;
}
