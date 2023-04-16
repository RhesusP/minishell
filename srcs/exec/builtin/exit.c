/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:21:45 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/16 17:41:16 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

/**
*	@brief Exit process when the single arg is non numerical
**/
static void	non_numerical_arg(char **cmd)
{
	printf("\nexit\nminishell: exit: %s: numeric argument required\n", cmd[i]);
	free_all(cmd); //WARNING : potentiel leak si on a une cmd du genre : exit | WORD ARG ARG --> En effet, on ne free que la commande exit ici + pas de free de la structure
	exit(0);
}

/**
*	@brief Exit process when exit is called without args
**/
static void	one_arg(char **cmd)
{
	free_all(cmd); //WARNING : potentiel leak si on a une cmd du genre : exit | WORD ARG ARG --> En effet, on ne free que la commande exit ici + pas de free de la structure
	printf("\nexit\n");
	exit(0);
}

/**
*	@brief Exit the minishell process
**/
void	exec_exit(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[1])
		one_arg(cmd);
	if (cmd[1] && cmd[2])
	{
		printf("\nexit\nminishell: exit: too many arguments\n");
		return ;
	}
	if (cmd[1])
	{
		while (cmd[1][i])
		{
			if (ft_is_numeric(cmd[i]) == FAILURE)
				non_numerical_arg(cmd);
			i++;
		}
		printf("\nexit\n");
		free_all(cmd); //WARNING : potentiel leak si on a une cmd du genre : exit | WORD ARG ARG --> En effet, on ne free que la commande exit ici + pas de free de la structure
		exit(ft_atoi(cmd[1]));
	}
}