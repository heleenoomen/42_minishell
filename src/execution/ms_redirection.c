/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:33:13 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/21 14:34:28 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* possible structure for executionn of the redirection nodes */

/* closes the filedescriptor that has to be substitued by the 
 * redirection. Then opens the redirection file, dups its file
 * descriptor and goes on to execute the exec node that follows
 * afterwards, closes and restores the filedescriptors
 */
void	runredir(struct cmd *cmd, t_env *env, bool *parent)
{
	struct redircmd	*rcmd;
	int				fd_cpy;
	int				file_fd;

	rcmd = (struct redircmd *) cmd;
	fd_cpy = dup(rcmd->fd);
	close(rcmd->fd);
	file_fd = open(rcmd->file, rcmd->mode);
	if (file_fd < 0)
	{
		perror(rcmd->file);
		return(return_or_exit(env, parent));
	}
	runcmd(rcmd->cmd, env, parent); // call the function that executes the exec command
	close(file_fd);
	dup(fd_cpy);
}
