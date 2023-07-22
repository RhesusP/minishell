/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:02:12 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 16:49:29 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Free the content of the to_free object and exit the program with the
 * given exit status.
 * 
 * @param f 
 * @param is_exit Boolean to exit or not the program.
 * @param exit_status
 * @param u Boolean to unlink the here files.
 */
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

/**
 * @brief Allocates (with malloc(3)) an array of int of size nb_pipes + 1.
 * 
 * @param nb_pipes 
 */
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

/**
 * @brief Initialize the global variables to_free.
 * @details The main goal of this structure is to free all the allocated
 * variables
 * @param nb_pipes number of pipes in the current command.
 * @param word word list of the current command.
 * @param line current line (retrieved by readline)
 */
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
