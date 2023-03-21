/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:27:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/03/19 19:20:55 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env_var	*env_vars;		//TODO rename type to a more generic name
	t_env_var	*global_vars;
	char		*line;
	t_word		**words_lst;

	if (argc != 1)
	{
		ft_putstr_fd("[!] USAGE: ./minishell\n", 2);
		return (0);
	}
	signal_handler();
	env_vars = get_environment(env);		//handle fail
	global_vars = malloc(sizeof(t_env_var));
	global_vars = 0;
	//add_back_env_var(&global_vars, create_env_var("TEST=test"));
	while (1)
	{
		line = readline("$> ");
		handle_ctrld(line);
		if (!is_cmd_anonymous(line))
			add_history(line);
		printf("you entered: %s\n", line);
		words_lst = parse_words(line, env_vars, &global_vars);
		execute_line(*words_lst, env_vars);
		free(line);
	}
	return (0);
}
