/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:27:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/02/27 21:54:04 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env_var	*env_var;
	t_word		*word;
	char		*line;

	if (argc != 1)
	{
		ft_putstr_fd("[!] USAGE: ./minishell\n", 2);
		return (0);
	}
	signal_handler();
	env_var = get_environment(env);		//handle fail
	print_env(env_var);
	while (1)
	{
		line = readline("$> ");
		handle_ctrld(line);
		if (!is_cmd_anonymous(line))
			add_history(line);
		printf("you entered: %s\n", line);
		word = parse_words(line);
		//execute_line(env_var);
		free(line);
	}
	return (0);
}
