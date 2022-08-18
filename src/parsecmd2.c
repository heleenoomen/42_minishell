/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:35:04 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/18 11:41:54 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct cmd	*parsepipe(char **s, char *es)
{
	if (peek(ps, es, "("))
		parse_block(ps, es, 0, 0);


struct cmd	*parsecmd(char *s)
{
	char		*es;
	struct cmd	*cmd;

	cmd = parsepipe(&s, es);
	nulterminate(cmd);
	return (cmd);
}
