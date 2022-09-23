/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_signal_sender.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 21:38:17 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/23 21:14:14 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_sigint(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_IGN;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGINT, &sn, NULL);
}

void	parent_sigquit(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_IGN;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGQUIT, &sn, NULL);
}

void	parent_send_signal(void)
{
	parent_sigint();
	parent_sigquit();
}

void	child_sigint(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_DFL;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGINT, &sn, NULL);
}

void	child_sigquit(void)
{
	struct sigaction	sn;

	sn.sa_handler = SIG_DFL;
	sn.sa_flags = SA_RESTART;
	sigemptyset(&sn.sa_mask);
	sigaction(SIGQUIT, &sn, NULL);
}

/* HO: I thought that for the children, sigint and sigquit both go to their defaults */
void	child_send_signal(void)
{
	child_sigint();
	child_sigquit();
}
