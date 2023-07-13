/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:31:55 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/13 13:11:38 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

static int	search_redir(t_word **lst, t_word *current, t_redir **redir)
{
	while (current)
	{
		if (type_is_redir(current))
		{
			if (current->next && (current->next->type == FILEPATH || \
				current->next->type == DELIMITER))
			{
				add_back_redir(redir, create_redir(current->type, \
					current->next->word));
				delete_word(current, lst);
				delete_word(current->next, lst);
			}
			else
			{
				perror("syntax error ?\n");
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

t_redir	**get_redir(t_word **lst)
{
	t_word	*current;
	t_redir	**redir;

	if (!*lst)
		return (0);
	current = *lst;
	redir = malloc(sizeof(t_redir *));
	if (!redir)
		return (0);
	*redir = 0;
	if (!search_redir(lst, current, redir))
		return (0);
	return (redir);
}

char	*here_doc(char *delim)
{
	char	*line;
	char	*concat;
	t_word	*arg;
	int		i;

	concat = "";
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
			break ;
		concat = ft_strjoin(concat, line);
		concat = ft_strjoin(concat, "\n");
	}
	return (concat);
}
