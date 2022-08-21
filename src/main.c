/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:45:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/21 14:55:03 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include "termios.h"
#include "termcap.h"

/* checks for unclosed quotes. If any, line is not even parsed */
int	unclosed_quotes(char *s)
{
	int		i;
	int		modus;
	
	modus = NO_QUOTES;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			change_quote_modus(&modus, s[i]);
		i++;
	}
	if (modus != NO_QUOTES)
		return (true);
	return (false);
}

/* general structure for minishell main function. Kany, I will 
 * clean this up when time comes ;-) Also, I pass now my t_env
 * struct to everywhere, but in the end we will of course pass
 * one general minishell struct in which we insert t_env.
 * I will adapt it.
 */
int	main(int argc, char **argv, char **envp)
{
	char			*buf;
	t_env			env;
	struct termios	termios_cpy;
	bool			parent;	

	(void)argc;
	(void)argv;

	init_env(&env, envp);
	ms_exit = 0;
	ms_signal(env);
	while (1)
	{
		cancel_echoctl();
		buf = readline("Minishell>>> ");
		if (buf  == NULL)
			break ;
		if (unclosed_quotes(buf))
		{
			dprintf(2, "Unclosed quotes\n");
			free(buf);
			rl_on_new_line();
			continue ;
		}
		ms_sigint_ignore(env);
		parent = true;
		runcmd(parsecmd(buf), &env, &parent);
		ms_sigint(env);
		add_history(buf);
		free(buf);
		buf = NULL;
	}
	clear_history();
	clear_env(&env);
	write(1, "\n", 1);
	ft_putstr_fd("exit\n", 1);
	reset_echoctl();
	return (1);
}
