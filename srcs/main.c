/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:27:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/02/25 14:38:01 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char				*line;

	if (argc != 1)
	{
		ft_putstr_fd("[!] USAGE: ./minishell\n", 2);
		return (0);
	}
	signal_handler();
	while (1)
	{
		line = readline("$> ");
		handle_ctrld(line);
		printf("you entered: %s\n", line);
		free(line);
	}
	return (0);
}
