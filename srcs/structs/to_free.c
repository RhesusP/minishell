/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:02:12 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/31 12:40:25 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_and_exit(t_to_free free_struct, int exit_status)
{
	ft_free(free_struct.env, free_struct.global);
	free_tubes(free_struct.tubes);
	free(free_struct.line);
	free_word_lst(free_struct.lst);
	free_word_lst(free_struct.command);
	exit(exit_status);
}
