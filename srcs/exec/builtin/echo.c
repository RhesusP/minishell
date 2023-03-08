/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbarde-c <tbarde-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:51:14 by tbarde-c          #+#    #+#             */
/*   Updated: 2023/03/08 12:44:13 by tbarde-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"
#include "../../../includes/exec.h"

/*
**	Echo with no option
*/
static void	exec_echo_no_option(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
}

/*
**	Echo -n
*/
static void	exec_echo_dash_n(char **cmd)
{
	int	i;

	i = 3;
	if (!cmd[2])
		return ;
	else
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], STDOUT_FILENO);
			//printf("%s", cmd[i]);
			if (cmd[i + 1])
			{
				ft_putstr_fd(" ", STDOUT_FILENO);
				//printf(" ");
			}
			i++;
		}
}

/*
**	Display the arg
**	-n : no newline after display
**	WARNING : DOESN'T WORK YET
*/
void	exec_echo(char **cmd)
{
	int	i;

	i = 0;
	if (!cmd[1])
		printf("\n");
	else if (cmd[1] == "-n")
		exec_echo_dash_n(cmd);
	else
		exec_echo_no_option(cmd);
}

/*
**	Main test	WARNING : TO ERASE
*/
int main()
{
	char **cmd;
	cmd = malloc(sizeof(char *) * 4);
	cmd[0] = "echo";
	cmd[1] = "-n";
	cmd[2] = "coucou";
	cmd[3] = NULL;
	exec_echo(cmd);
	free(cmd);
	return 0;
}