/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:37:25 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 11:40:01 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

char	*get_quoted(char *str, t_env_var **env)
{
	int		size;
	char	**tab;
	char	*res;
	char	*temp;
	int		i;

	size = get_nb_quoted_words(str);
	tab = fill_quoted_tab(str, size);
	i = -1;
	while (++i < size)
	{
		if (tab[i][0] != '\'')
		{
			tab[i] = get_vars(tab[i], env);
		}
		if (tab[i][0] == '\'' || tab[i][0] == '"')
		{
			temp = remove_quotes(tab[i]);
			free(tab[i]);
			tab[i] = temp;
		}
	}
	res = join_tab(tab, size);
	free_all(tab);
	return (res);
}

void	var_expansion(t_word **words_lst, t_env_var **e)
{
	t_word	*current;
	char	*temp;

	if (!words_lst || !*words_lst)
		return ;
	current = *words_lst;
	while (current)
	{
		temp = get_quoted(current->word, e);
		free(current->word);
		current->word = temp;
		current = current->next;
	}
}
