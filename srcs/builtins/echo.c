/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:51:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/17 16:46:11 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	arg_is_valid(char *arg)
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

static void	display_echo(t_word *current, int *has_write)
{
	g_status = 0;
	if (*has_write == 1)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd(current->word, 1);
	*has_write = 1;
}

void	ft_echo(t_word **lst)
{
	t_word	*current;
	int		newline;
	int		accept_option;
	int		has_write;

	has_write = 0;
	accept_option = 1;
	newline = 1;
	current = *lst;
	while (current)
	{
		if (current->type == ARG)
		{
			if (accept_option && arg_is_valid(current->word))
				newline = 0;
			else
			{
				display_echo(current, &has_write);
				accept_option = 0;
			}
		}
		current = current->next;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}
