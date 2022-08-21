/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:27:51 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/21 14:33:05 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* possible structure for execution of pipe nodes */

/* handles the pipe nodes
 */
void	runpipe(struct cmd *cmd, t_env *env, bool *parent)
{
	int				p[2];
	struct pipecmd	*pcmd;
	int				status;
	int				pid[2];

	pcmd = (struct pipecmd *) cmd;
	if (pipe(p) < 0)
	{
		perror("pipe");
		ms_exit = errno;
		return (return_or_exit(env, parent));		
	}
	pid[0] = fork();
	if (pid[0] == 0)
	{
		*parent = false;
		ms_sig_dfl(env);
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left, env, parent);
		exit(0);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		*parent = false;
		ms_sig_dfl(env);
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right, env, parent);
		exit(0);
	}
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], &status, 0);
	if (WIFEXITED(status))
		ms_exit = WEXITSTATUS(status);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		ms_exit = WEXITSTATUS(status);
	return (return_or_exit(env, parent));
}
