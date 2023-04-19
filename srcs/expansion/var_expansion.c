/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:37:25 by cbernot           #+#    #+#             */
/*   Updated: 2023/04/19 16:46:33 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

int	is_single_quoted(char *str)
{
	int	i;
	int	nb_single;

	i = 0;
	nb_single = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			nb_single++;
		i++;
	}
	if (nb_single == 2)
		return (1);
	return (0);
}

char	*remove_single_quotes(char *str)
{
	int	len_before;
	int	len_between;
	char	*bef;
	char	*bet;
	char	*aft;
	char 	*res;
	char	*temp;

	len_before = 0;
	while (str[len_before] != '\0' && str[len_before] != '\'')
		len_before++;
	bef = ft_strndup(str, len_before);
	len_between = len_before + 1;
	while (str[len_between] != '\0' && str[len_between] != '\'')
		len_between++;
	bet = ft_strndup(&str[len_before + 1], len_between - 1);
	aft = ft_strdup(&str[len_between + 1]);
	temp = ft_strjoin(bef, bet);
	res = ft_strjoin(temp, aft);
	free(temp);
	free(bef);
	free(bet);
	free(aft);
	free(str);
	return (res);
}

t_word	**var_expansion(t_word **words_lst, t_env_var **global_vars, t_env_var **env_vars)
{
	t_word	*current;

	if (!*words_lst)
		return (words_lst);
	current = *words_lst;
	while (current)
	{
		if (is_single_quoted(current->word))
		{
			current->word = remove_single_quotes(current->word);
			printf("\033[35m%s is single quoted\033[39m\n", current->word);
		}
		// if (ft_strchr(current->word, '$'))
		// {
		// 	printf("variable detected\n");

		// }
		current = current->next;
	}


	return (words_lst);
}