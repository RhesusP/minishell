/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:51:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/22 16:53:48 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Check if the "-n" option is valid.
 * @details Accepts "-n", "-nn", "-nnn", "-n -n" etc.
 * @param arg 
 * @return 1 if the option is valid, 0 otherwise.
 */
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

/**
 * @brief Print a single argument.
 * 
 * @param current Argument to print.
 * @param has_write Boolean to know if something has been already written
 * (to know if we need to print a space before the argument)
 */
static void	display_echo(t_word *current, int *has_write)
{
	g_gbl.status = 0;
	if (*has_write == 1)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd(current->word, 1);
	*has_write = 1;
}

/**
 * @brief Print the arguments.
 * @details If the first argument is "-n", it does not print a new line.
 * @param lst Sub-command to execute.
 */
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
