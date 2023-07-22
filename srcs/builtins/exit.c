/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:21:45 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/07/22 14:43:24 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief Atoi for long integer.
 * 
 * @param str String to convert into a long integer.
 * @return long The converted string.
 */
static long	ft_long_atoi(const char *str)
{
	long		res;
	size_t		i;
	int			sign;

	res = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

static int	ft_get_neg_long_len(long nbr)
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

/**
 * @brief Check if a string is a valid long int.
 * 
 * @param str Number to check.
 * @return 1 if the string is a valid long int, 0 otherwise.
 */
static int	ft_long_limit_error(char *str)
{
	int		len_str;
	int		len_nbr;
	long	nbr;

	len_str = ft_strlen(str);
	nbr = ft_long_atoi(str);
	len_nbr = 0;
	if (nbr <= 0)
		len_nbr = ft_get_neg_long_len(nbr);
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

/**
 * @brief Print an error message and exit the shell.
 * 
 * @param to_free
 * @param current 
 */
static void	handle_multiple_args(t_to_free to_free, t_word *current)
{
	if (ft_long_limit_error(current->next->word) == 0)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		g_gbl.status = 1;
	}
	else
	{
		ft_putendl_fd("exit: numeric argument required", 2);
		free_and_exit(&to_free, 1, 2, 1);
	}
}

/**
 * @brief Exit the shell.
 * @details If no argument is passed, exit with the last command status.
 * If a parameter is passed, exit with the parameter value % 255. If multiple
 * parameters are passed or if the parameter if > 9223372036854775807,
 * exit with an error.
 * @param to_free 
 */
void	ft_exit(t_to_free to_free)
{
	int		nb_arg;
	int		exit_value;
	t_word	*current;

	printf("exit\n");
	nb_arg = get_nb_arg(to_free.command);
	if (nb_arg == 0)
		free_and_exit(&to_free, 1, g_gbl.status, 1);
	current = *(to_free.command);
	if (nb_arg == 1)
	{
		if (ft_long_limit_error(current->next->word) == 0)
			exit_value = ft_atoi(current->next->word);
		else
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			exit_value = 2;
		}
		free_and_exit(&to_free, 1, exit_value % 256, 1);
	}
	else
		handle_multiple_args(to_free, current);
}
