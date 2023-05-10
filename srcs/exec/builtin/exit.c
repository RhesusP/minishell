/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:21:45 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/05 16:36:39 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	get_nb_arg(t_word **lst)
{
	t_word	*current;
	int		nb;

	nb = 0;
	current = *lst;
	while (current)
	{
		if (current->type == ARG)
			nb++;
		current = current->next;
	}
	return (nb);
}

int	ft_get_neg_int_len(int nbr)
{
	int	len_nbr;

	len_nbr = 0;
	while (nbr < 0)
	{
		nbr /= 10;
		len_nbr++;
	}
	return (len_nbr + 1);
}

int	ft_int_limit_error(char *str)
{
	int	len_str;
	int	len_nbr;
	int	nbr;

	len_str = ft_strlen(str);
	nbr = ft_atoi(str);
	len_nbr = 0;
	if (nbr <= 0)
		len_nbr = ft_get_neg_int_len(nbr);
	else
	{
		while (nbr > 0)
		{
			nbr /= 10;
			len_nbr++;
		}
	}
	if (nbr >= 0 && str[0] == '+')
		len_str--;
	if (ft_isalpha(str[0]))
		return (1);
	if (len_nbr != len_str)
		return (1);
	return (0);
}

void	ft_exit(t_word **lst)
{
	int	nb_arg;
	int	exit_value;
	t_word	*current;

	printf("exit\n");
	nb_arg = get_nb_arg(lst);
	if (nb_arg == 0)
		exit (0);
	current = *lst;
	if (nb_arg == 1)
	{
		if (ft_int_limit_error(current->next->word) == 0)
			exit_value = ft_atoi(current->next->word);
		else
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			exit_value = 0;		//TODO global var for $?
		}
		printf("exiting with status code %d\n", exit_value);
		exit(exit_value);
	}
	else
	{
		if (ft_int_limit_error(current->next->word) == 0)
			ft_putendl_fd("exit: too many arguments", 2);
		else
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			exit(0);
		}
	}
}