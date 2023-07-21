/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:02:12 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 11:43:37 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit(t_to_free f, int is_exit, int exit_status)
{
	free(f.pids);
	ft_free(*(f.env));
	free(f.line);
	free_word_lst(f.lst);
	free_word_lst(f.command);
	if (is_exit)
		exit(exit_status);
}

void	init_to_free(t_to_free *f, int nb_pipes, t_word **word, char *line)
{
	int	i;

	f->pids = malloc(sizeof(int) * (nb_pipes + 1));
	if (!f->pids)
		return ;
	f->he_files = malloc(sizeof(char *) * (nb_pipes + 2));
	if (!f->he_files)
		return ;
	i = 0;
	while (i < nb_pipes + 2)
	{
		f->he_files[i] = 0;
		i++;
	}
	f->lst = word;
	f->line = line;
	f->command = malloc(sizeof(t_word *));
	if (!f->command)
		return ;
	*(f->command) = 0;
}
