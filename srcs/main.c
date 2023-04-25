/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:27:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/04/25 11:20:32 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	check_pipe_syntax(t_word **lst)
{
	return (1);		//TODO maybe useful ? (need to check execve behavior)
	// t_word	*current;

	// if (!*lst)
	// 	return (0);
	// current = *lst;
	// if (current->type == PIPE)
	// while (current)
	// {
	// 	if ()
	// 	current = current->next;
	// }
}

int	main(int argc, char **argv, char **env)
{
	t_env_var	*env_vars;		//TODO rename type to a more generic name
	t_env_var	*global_vars;
	char		*line;
	char		*tmp;
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
		printf("\033[1;34m%s\033[00m", get_pwd(env_vars)->values[0]);
		line = readline("$ ");
		handle_ctrld(line);
		if (!is_cmd_anonymous(line))
			add_history(line);
		words_lst = parse_words(line, env_vars, &global_vars);
		display_words(words_lst);
		var_expansion(words_lst, &global_vars, &env_vars);
		if (words_lst && *words_lst && check_pipe_syntax(words_lst))
			execute_line(words_lst, env_vars);
		free(line);
	}
	return (0);
}
