/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:29:10 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/12 16:43:17 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_word	*create_word(char *cmd)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (0);
	word->word = cmd;
	word->type = 0;
	word->len = 0;
	word->next = 0;
	word->prev = 0;
	return (word);
}

t_word	*get_last_word(t_word *lst)
{
	t_word	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_back_word(t_word **lst, t_word *new)
{
	t_word	*last;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	last = get_last_word(*lst);
	last->next = new;
}

void	display_words(t_word **lst)
{
	t_word	*current;

	printf("display words called\n");
	if (!*lst)
	{
		printf("######   TOKEN LIST   ######\n");
		printf("Aucun commande.\n");
		return ;
	}
	current = *lst;
	printf("######   TOKEN LIST   ######\n");
	while (current)
	{
		printf("%d\t%s\n", current->type, current->word);
		current = current->next;
	}
}

void	clear_word_lst(t_word **lst)
{
	t_word	*current;
	t_word	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	*lst = 0;
}

void	insert_word(t_word **lst, t_word *new, t_word *prev)
{
	t_word	*next;

	if (!lst || !prev)
		return ;
	next = prev->next;
	prev->next = new;
	new->next = next;
}

void	delete_word(t_word **lst, t_word *to_del)
{
	t_word	*next;
	t_word	*current;
	t_word	*prev;

	if (!lst || !to_del)
		return ;
	current = *lst;
	while (current->next != to_del)
	{
		prev = current;
		current = current->next;
	}
	prev->next = to_del->next;
	free(to_del);
}

void	free_word_lst(t_word **lst)
{
	t_word	*current;
	t_word	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
	free(lst);
}