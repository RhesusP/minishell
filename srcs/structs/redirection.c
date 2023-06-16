/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:10:12 by cbernot           #+#    #+#             */
/*   Updated: 2023/06/16 11:01:19 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_redir	*create_redir(t_type type, char *path)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (0);
	redir->type = type;
	redir->filepath = ft_strdup(path);
	redir->next = 0;
	return (redir);
}

static t_redir	*get_last_redir(t_redir *lst)
{
	t_redir	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_back_redir(t_redir **lst, t_redir *new)
{
	t_redir	*last;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	last = get_last_redir(*lst);
	last->next = new;
}

void	free_redir(t_redir **redir)
{
	t_redir	*current;
	t_redir	*next;

	current = *redir;
	while (current)
	{
		next = current->next;
		free(current->filepath);
		free(current);
		current = next;
	}
	free(redir);
}

int	type_is_redir(t_word *word)
{
	if (word->type == RI || \
		word->type == RO || \
		word->type == ARO || \
		word->type == HE)
		return (1);
	return (0);
}
