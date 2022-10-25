/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:45:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/25 14:23:59 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* general structure for minishell main function. Kany, I will 
 * clean this up when time comes ;-) Also, I pass now my t_env
 * struct to everywhere, but in the end we will of course pass
 * one general minishell struct in which we insert t_env.
 * I will adapt it.
 */
	// (void)argc;
	// (void)argv;
	//free_minishell(&minishell);
int	main(int argc, char **argv, char **envp)
{
	char			*buf;
	t_minishell		minishell;

	g_global_exit_status = 0;
	init_minishell(&minishell, envp);
	buf = NULL;
	while (1)
	{
		signals_interactive_mode(&(minishell.termios_cpy));
		free(buf);
		buf = readline("Minishell>>> ");
		if (buf == NULL)
			break ;
		if (*buf == '\0')
			continue ;
		main_executor(buf, &minishell);
		add_history(buf);
		buf = NULL;
	}
	clear_history();
	ft_putstr_fd("exit\n", 1);
	reset_echoctl(&(minishell.termios_cpy));
	return (g_global_exit_status);
}
