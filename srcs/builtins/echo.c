/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:51:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/21 02:26:54 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arg_is_valid(char *arg)
{
	int	i;

	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		i = 2;
		while (arg[i] != '\0')
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(t_word **lst)
{
	t_word	*current;
	int		newline;
	int		accept_option;

	accept_option = 1;
	newline = 1;
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		if (accept_option && arg_is_valid(current->word))
			newline = 0;
		else
		{
			if (current->next && current->next->type == ARG)
			{
				ft_putstr_fd(current->word, 1);
				ft_putchar_fd(' ', 1);
			}
			else
				ft_putstr_fd(current->word, 1);
			accept_option = 0;
		}
		current = current->next;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
	//exit(EXIT_SUCCESS);		//TODO maybe fix the multiple exit case
}
