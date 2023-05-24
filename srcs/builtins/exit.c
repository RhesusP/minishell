/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:21:45 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/05/21 15:58:37 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	ft_isspace(const char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

long	ft_long_atoi(const char *str)
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

int	ft_get_neg_long_len(long nbr)
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

int	ft_long_limit_error(char *str)
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

void	ft_exit(t_word **lst, t_env_var **env, t_env_var **global, t_word **words, char *line, int **tubes)
{
	int		nb_arg;
	int		exit_value;
	t_word	*current;

	printf("exit\n");
	nb_arg = get_nb_arg(lst);
	if (nb_arg == 0)
	{
		ft_free(*env, *global);
		free_tubes(tubes);
		free(line);
		free_word_lst(lst);
		free_word_lst(words);
		exit(g_status);
	}
	current = *lst;
	if (nb_arg == 1)
	{
		if (ft_long_limit_error(current->next->word) == 0)
			exit_value = ft_atoi(current->next->word);
		else
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			exit_value = 2;
		}
		ft_free(*env, *global);
		free_tubes(tubes);
		free(line);
		free_word_lst(lst);
		free_word_lst(words);
		exit(exit_value % 256);
	}
	else
	{
		if (ft_long_limit_error(current->next->word) == 0)
		{
			ft_putendl_fd("exit: too many arguments", 2);
			g_status = 1;
		}
		else
		{
			ft_putendl_fd("exit: numeric argument required", 2);
			ft_free(*env, *global);
			free_tubes(tubes);
			free(line);
			free_word_lst(lst);
			free_word_lst(words);
			exit(2);
		}
	}
}