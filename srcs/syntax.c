/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:24:33 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 10:51:23 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static int	is_bad_filepath(t_word *word)
{
	if (word->type == FILEPATH)
	{
		if (ft_strcmp(">", word->word) == 0 || \
			ft_strcmp("<", word->word) == 0 || \
			ft_strcmp(">>", word->word) == 0 || \
			ft_strcmp("<<", word->word) == 0)
			return (1);
	}
	return (0);
}

static int	print_syntax_error(char *token)
{
	g_status = 2;
	ft_putstr_fd("syntax error near unexpected token '", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	return (1);
}

int	syntax_error(t_word **lst)
{
	t_word	*current;

	if (!lst || !*lst)
		return (0);
	current = *lst;
	while (current)
	{
		if (type_is_redir(current) && !current->next)
			return (print_syntax_error("newline"));
		if (current->next)
		{
			if (type_is_redir(current) && \
				(type_is_redir(current->next) || \
				is_bad_filepath(current->next)))
				return (print_syntax_error(current->next->word));
		}
		current = current->next;
	}
	return (0);
}