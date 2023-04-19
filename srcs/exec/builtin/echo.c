/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:51:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/04/19 15:29:45 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

int	arg_is_valid(char *arg)
{
	int	i;

	if (ft_strncmp(arg, "-n", 2) == 0)
	{
		i = 2;
		while (arg[i] != '\0')
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(t_word **lst, int **tubes, int count, int nb_pipes)
{
	t_word	*current;
	int		newline;
	int		accept_option;

	t_redir		**redir;
	int			pid;
	char		**full_cmd;
	pid = fork();
	redir = get_redir(lst);

	if (pid == -1)
	{
		perror("failed to fork\n");
	}
	if (pid > 0)		//parent process
	{
		if (count > 0)
		{
			close(tubes[count - 1][0]);
			close(tubes[count - 1][1]);
		}
		wait(NULL);
	}
	if (pid == 0)		//child process
	{
		if (count > 0)
		{
			dup2(tubes[count - 1][0], STDIN_FILENO);	//duplique la sortie du précedent sur l'entree de l'actuel
			close(tubes[count - 1][0]);					//ferme l'entrée / sortie du précédent
			close(tubes[count - 1][1]);
		}
		if (count < nb_pipes)
		{
			dup2(tubes[count][1], STDOUT_FILENO);	//duplique pour le suivant
			close(tubes[count][0]);
			close(tubes[count][1]);
		}
		full_cmd = lst_to_string(lst);

		if (redir)
			full_cmd = handle_redirection(redir, full_cmd);

		accept_option = 1;
		newline = 1;
		current = *lst;
		while (current && current->type != ARG)
			current = current->next;
		while (current && current->type == ARG)
		{
			if (accept_option && arg_is_valid(current->word))
				newline = 0;
			else
			{
				if (current->next && current->next->type == ARG)
				{
					ft_putstr_fd(current->word, 1);
					ft_putchar_fd(' ', 1);
				}
				else
					ft_putstr_fd(current->word, 1);
				accept_option = 0;
			}
			current = current->next;
		}
		if (newline)
			ft_putchar_fd('\n', 1);
		exit(EXIT_SUCCESS);		//TODO maybe fix the multiple exit case
	}

}
