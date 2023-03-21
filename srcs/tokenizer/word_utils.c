/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:29:10 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/19 18:19:22 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_word	*create_word(char *cmd)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (0);
	word->word = cmd;
	word->type = INIT;
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
	new->prev = last;
	last->next = new;
}

void	display_words(t_word **lst)
{
	t_word	*current;

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
		printf("%s\t%s\n", print_type(current->type), current->word);
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

void	free_word_lst(t_word **lst)
{
	t_word	*current;
	t_word	*next;

	if (!*lst)
		return ;
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

void	delete_word(t_word *word, t_word **lst)
{
	t_word	*prev;
	t_word	*next;

	prev = word->prev;
	next = word->next;
	if (!next)
		prev->next = 0;
	else if (!prev)
	{
		*lst = next;
		next->prev = 0;
	}
	else
	{
		prev->next = next;
		next->prev = prev;
	}
}

void	reverse_display_words(t_word **lst)
{
	t_word	*last;

	last = get_last_word(*lst);
	if (!last)
	{
		printf("######   REVERSE TOKEN LIST   ######\n");
		printf("Aucun commande.\n");
		return ;
	}
	printf("######   REVERSE TOKEN LIST   ######\n");
	while (last)
	{
		printf("%s\t%s\n", print_type(last->type), last->word);
		last = last->prev;
	}
}