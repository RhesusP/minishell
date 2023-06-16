/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 08:37:25 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:47:45 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static char	*get_quoted(char *str, t_env_var **env, t_env_var **global)
{
	int		size;
	char	**tab;
	char	*res;
	char	*temp;
	int		i;

	i = -1;
	size = get_nb_quoted_words(str);
	tab = fill_quoted_tab(str, size);
	while (++i < size)
	{
		if (tab[i][0] != '\'')
			tab[i] = get_vars(tab[i], env, global);
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

void	var_expansion(t_word **lst, t_env_var **g, t_env_var **e)
{
	t_word	*current;
	int		quoted_case;
	char	*temp;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		temp = get_quoted(current->word, e, g);
		free(current->word);
		current->word = temp;
		current = current->next;
	}
}
