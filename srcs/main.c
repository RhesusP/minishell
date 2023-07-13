/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbernot <cbernot@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:27:54 by cbernot           #+#    #+#             */
/*   Updated: 2023/07/13 13:37:55 by cbernot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	g_status = 0;

static void	handle_error(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("[!] USAGE: ./minishell\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	display_t_word_lst(t_word **lst)
{
	t_word	*current;

	current = *lst;
	while (current)
	{
		printf("%s\t", current->word);
		printf("type: %d\n", current->type);
		current = current->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env_var	*env_vars;
	t_env_var	*global_vars;
	char		*line;
	t_word		**words_lst;

	handle_error(argc, argv);
	signal_handler();
	env_vars = get_environment(envp);
	global_vars = NULL;
	while (1)
	{
		line = readline("\033[1;36mminishell $>\033[00m ");
		handle_ctrld(line, env_vars, global_vars);
		words_lst = parse_words(line, &global_vars);
		var_expansion(words_lst, &global_vars, &env_vars);

		if (words_lst && *words_lst && !syntax_error(words_lst))
			execute_line(words_lst, &env_vars, &global_vars, line);
		add_history(line);
		free(line);
		free_word_lst(words_lst);
	}
	ft_free(env_vars, global_vars);
	return (0);
}
