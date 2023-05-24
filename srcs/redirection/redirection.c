/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 21:10:12 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/21 01:41:54 by cbernot          ###   ########.fr       */
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

t_redir	*get_last_redir(t_redir *lst)
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

void	display_redirs(t_redir **lst)
{
	t_redir	*current;

	if (!*lst)
	{
		printf("######   REDIR LIST   ######\n");
		printf("Aucun commande.\n");
		return ;
	}
	current = *lst;
	printf("######   REDIR LIST   ######\n");
	while (current)
	{
		printf("\t%s\n", current->filepath);
		current = current->next;
	}
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