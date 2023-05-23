/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:27:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/05/21 16:25:36 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	g_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_env_var	*env_vars;
	t_env_var	*global_vars;
	char		*line;
	t_word		**words_lst;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("[!] USAGE: ./minishell\n", 2);
		return (0);
	}
	signal_handler();
	env_vars = get_environment(envp);
	global_vars = NULL;
	while (1)
	{
		line = readline("\033[1;36mminishell $>\033[00m ");
		handle_ctrld(line, env_vars, global_vars);
		if (!is_cmd_anonymous(line))
			add_history(line);

		words_lst = parse_words(line, &global_vars);
		var_expansion(words_lst, &global_vars, &env_vars);
		// display_words(words_lst);
		if (words_lst && *words_lst && !syntax_error(words_lst))
			execute_line(words_lst, &env_vars, &global_vars, line);
		free(line);
		free_word_lst(words_lst);
	}
	ft_free(env_vars, global_vars);
	return (0);
}
