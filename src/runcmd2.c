/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:36:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 13:23:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	return_or_exit(t_env *env, bool *parent)
{
	if (*parent == true)
		return ;
	clear_env(env);
	exit(ms_exit);
}

void	runexecfork(char *path, char **argv, char **envp)
{
	int	pid;
	int	status;

	pid = fork1();
	if (pid ==  0)
	{
		execve(path, argv, envp);
		perror(argv[0]);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms_exit = WEXITSTATUS(status);
}

void	runexec(struct cmd *cmd, t_env *env, bool *parent)
{
	struct execcmd	*ecmd;
	char			**argv;
	char			**envp;
	char			*path;

	ecmd = (struct execcmd *) cmd;
	if (ecmd->argv[0] == NULL)
		return_or_exit(env, parent);
	argv = expander(ecmd->argv, env, true, true);
	if (builtin(argv, env))
	{
		if (*pipe)
			exit(0);
			return ;
	}
	envp = make_envp(env);
	path = find_path(argv[0], env, parent);
	if (*parent == true)
	{
		runexecfork(path, argv, envp);
		return ;
	}
	execve(path, argv, envp);
	perror(argv[0]);
}

void	runredir(struct cmd *cmd, t_env *env, bool *parent)
{
	struct redircmd	*rcmd;

	rcmd = (struct redircmd *) cmd;
	close(rcmd->fd);
	if (open(rcmd->file, rcmd->mode) < 0)
	{
		perror(rcmd->file);
		if (*parent == false)
			exit(1);
		ms_exit = 1;
		return ;
	}
	runcmd(cmd, env, parent);
}

void	runhere(struct cmd *cmd, t_env *env, bool *parent)
{
	(void)cmd;
	(void)env;
	(void)parent;
}

void	runand(struct cmd *cmd, t_env *env, bool *parent)
{
	(void)cmd;
	(void)env;
	(void)parent;
}

void	runor(struct cmd *cmd, t_env *env, bool *parent)
{
	(void)cmd;
	(void)env;
	(void)parent;
}

void	runblock(struct cmd *cmd, t_env *env, bool *parent)
{
	(void)cmd;
	(void)env;
	(void)parent;
}

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
		return_or_exit(env, parent);		
	}
	pid[0] = fork1();
	if (p[0] == 0)
	{
		*parent = false;
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left, env, parent);
	}
	pid[1] = fork1();
	if (pid[1] == 0)
	{
		*parent = false;
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right, env, parent);
	}
	close(p[0]);
	close(p[1]);
	waitpid(p[0], &status, 0);
	if (WIFEXITED(status))
		ms_exit = WEXITSTATUS(status);
	waitpid(p[1], &status, 0);
	if (WIFEXITED(status))
		ms_exit = WEXITSTATUS(status);
	return_or_exit(env, parent);
}

void	runcmd(struct cmd *cmd, t_env *env, bool *parent)
{
	if (cmd->type == EXEC)
		runexec(cmd, env, parent);
	else if (cmd->type == REDIR)
		runredir(cmd, env, parent);
	else if (cmd->type == HERE)
		runhere(cmd, env, parent);
	else if (cmd->type == PIPE)
		runpipe(cmd, env, parent);
	else if (cmd->type == LIST)
		runand(cmd, env, parent);
//	else if (cmd->type == OR)
//		runor(cmd, env, parent);
	else
		runblock(cmd, env, parent);
	return_or_exit(env, parent);
}
