/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:28:46 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 14:00:03 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

void	exec_pipe()
{
	int	fd[2];
	int	pid;

	
	if (pipe(fd) == -1)
		return(FAILURE);
	pid = fork();
	if (pid == -1)
		return (FAILURE);
	if (pid == 0)
	{
		
	}
}