/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 22:29:10 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/20 17:14:02 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../includes/minishell.h"

t_word	*create_word(char *cmd)
{
	t_word	*word;

	word = malloc(sizeof(t_word));
	if (!word)
		return (0);
	word->word = ft_strdup(cmd);
	word->type = INIT;
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

char	*print_type(t_type type)
{
	if (type == CMD)
		return ("CMD");
	else if (type == ARG)
		return ("ARG");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == RI)
		return ("RI");
	else if (type == RO)
		return ("RO");
	else if (type == ARO)
		return ("ARO");
	else if (type == HE)
		return ("HE");
	else if (type == FILEPATH)
		return ("FILEPATH");
	else if (type == DELIMITER)
		return ("DELIMITER");
	else if (type == IGN)
		return ("IGN");
	else if (type == INIT)
		return ("INIT");
	else
		return ("UNKNOWN TYPE");
}

void	display_words(t_word **lst)
{
	t_word	*current;

	if (!lst || !*lst)
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
