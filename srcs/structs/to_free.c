/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:02:12 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/12 08:01:06 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit(t_to_free f, int is_exit, int exit_status)
{
	ft_free(*(f.env), *(f.global));
	free(f.line);
	free_word_lst(f.lst);
	free_word_lst(f.command);
	if (is_exit)
		exit(exit_status);
}
