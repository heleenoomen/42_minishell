/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:45:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/24 13:04:41 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/* general structure for minishell main function. Kany, I will 
 * clean this up when time comes ;-) Also, I pass now my t_env
 * struct to everywhere, but in the end we will of course pass
 * one general minishell struct in which we insert t_env.
 * I will adapt it.
 */
int	main(int argc, char **argv, char **envp)
{
	char			*buf;
	t_minishell		minishell;

	(void)argc;
	(void)argv;
	g_global_exit_status = 0;
	init_minishell(&minishell, envp);
	while (1)
	{
		cancel_echoctl(&(minishell.termios_cpy));
		signals_interactive_mode();
		buf = readline("Minishell>>> ");
		if (buf  == NULL)
			break ;
		if (*buf == '\0')
			continue ;
		main_executor(buf, &minishell);
		add_history(buf);
		free(buf);
		buf = NULL;
	}
	clear_history();
	/* clear minishell struct */
	ft_putstr_fd("exit\n", 1);
	reset_echoctl(&(minishell.termios_cpy));
	return (g_global_exit_status);
}

