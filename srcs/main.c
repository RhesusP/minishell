/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:27:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/15 10:27:14 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env_var	*env_vars;		//TODO rename type to a more generic name
	t_env_var	*global_vars;
	char		*line;

	if (argc != 1)
	{
		ft_putstr_fd("[!] USAGE: ./minishell\n", 2);
		return (0);
	}
	signal_handler();
	env_vars = get_environment(env);		//handle fail
	global_vars = 0;
	print_env(env_vars);
	print_env(global_vars);
	while (1)
	{
		line = readline("$> ");
		handle_ctrld(line);
		if (!is_cmd_anonymous(line))
			add_history(line);
		printf("you entered: %s\n", line);
		parse_words(line, env_vars, global_vars);
		free(line);
	}
	return (0);
}
