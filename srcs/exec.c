/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:52:44 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/02/28 14:04:43 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/exec.h"


/*
**	Get the command with args from the parser
**	Then we'll be able to pass the full command to execve()
*/
char	*get_full_cmd(t_word *parse)
{
	char	*cmd;
	char	*temp;
	cmd = NULL;
	if (parse->type == WORD)
	{
		cmd = ft_strdup(parse->word);
		parse = parse->next;
		while (parse && parse->type == ARG)
		{
			temp = cmd;
			cmd = ft_strjoin_spaced(cmd, parse->word);
			free(temp);
			parse = parse->next;
		}
	}
	return (cmd);
}

void	execute_cmd(t_word word, char *path)
{
	int	pid;

	pid = fork();
	if (pid > 0)
		wait(NULL);
	if (pid == 0)
	{

	}
}

/*
**	Test main ---WARNING : ERASE IT BEFORE PUSH
*/
int	main()
{
	t_word	parse1;
	t_word	parse2;
	t_word	parse3;
	t_word	parse4;
	char	*res;
	

	parse1.word = "ls";
	parse1.type = WORD;
	parse2.word = "-la";
	parse2.type = ARG;
	parse3.word = "-oi";
	parse3.type = ARG;
	parse4.word = "-us";
	parse4.type = ARG;

	parse1.next = &parse2;
	parse2.next = &parse3;
	parse3.next = &parse4;
	parse4.next = NULL;

	res = get_full_cmd(&parse1);
	printf("res is : %s\n", res);
	free(res);
	return 0;
}
