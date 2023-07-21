/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:27:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/21 13:36:54 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_to_free	g_gbl = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/// @brief Exit program if there is more than one arg
static void	handle_error(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("[!] USAGE: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env_var	*env_vars;
	char		*line;
	t_word		**words_lst;

	handle_error(argc, argv);
	env_vars = get_environment(envp);
	while (1)
	{
		signal_handler(1);
		line = readline("\033[1;36mminishell $>\033[00m ");
		handle_ctrld(line, env_vars);
		words_lst = parse_words(line);
		var_expansion(words_lst, &env_vars);
		if (words_lst && *words_lst && !syntax_error(words_lst))
			execute_line(words_lst, &env_vars, line);
		if (line && ft_strlen(line) > 0)
			add_history(line);
		free(line);
		free_word_lst(words_lst);
	}
	ft_free(env_vars);
	return (0);
}
