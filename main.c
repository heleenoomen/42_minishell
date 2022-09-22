/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:45:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/22 20:28:06 by hoomen           ###   ########.fr       */
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
	struct termios	termios_cpy;	

	(void)argc;
	(void)argv;
	g_global_exit_status = 0;
	init_minishell(&minishell, envp);
	while (1)
	{
		cancel_echoctl(&termios_cpy);
		signal_interactive_mode();
		buf = readline("Minishell>>> ");
		if (buf  == NULL)
			break ;
		main_executor(buf, &minishell);
		if (buf[0] != '\0')
			add_history(buf);
		free(buf);
		buf = NULL;
	}
	clear_history();
	/* clear minishell struct */
	write(1, "\n", 1);
	ft_putstr_fd("exit\n", 1);
	reset_echoctl(&termios_cpy);
	return (g_global_exit_status);
}

