/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:29:10 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/01 01:35:09 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_word	*create_word(char *cmd, t_type type)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (0);
	word->word = cmd;
	word->type = type;
	word->len = 0;
	word->next = 0;
	word->prev = 0;
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