/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:13:50 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/21 14:42:46 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

/* possible structure for execution of heredoc nodes */

void	runheredoc(struct *cmd, t_env *env, bool *parent)
{
			hcmd = (struct herecmd*)cmd;
			if (pipe(p) < 0)
				panic("pipe", NULL);
			if (fork1() == 0)
			{
				*parent = false;
				ms_sig_dfl(void);
				close(p[0]);
				while (1)
				{
					line = readline("pipe heredoc > ");
					len = strlen(line);
					if (line == NULL)
						break ;
					if (strcmp(line, hcmd->limit) == 0)
						break ;
					write(p[1], line, strlen(line));
					write(p[1], "\n", 1);
					free(line);
				}
				close(p[1]);
				exit(0);
			}
			close(p[1]);
			signal(SIGINT, SIG_IGN);
			wait (0);
			if (fork1() == 0)
			{
				*paret = false;
				ms_sig_dfl(void);
				close(0);
				dup(p[0]);
				close(p[0]);
				runcmd(hcmd->cmd, env);
			}
			close(p[0]);
			wait (0);
			return (returen_or_exit(env, parent));
}
