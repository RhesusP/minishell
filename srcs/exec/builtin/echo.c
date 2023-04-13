/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:51:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/13 11:36:32 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

void	ft_echo(t_word **lst)
{
	t_word	*current;
	int		newline;

	newline = 0;
	current = *lst;
	while (current && current->type != ARG)
		current = current->next;
	while (current && current->type == ARG)
	{
		if (ft_strcmp(current->word, "-n") == 0)
			newline = 1;
		else
			printf("%s ", current->word);
		current = current->next;
	}
	if (!newline)
		printf("\n");
}
