/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 19:36:05 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 18:34:16 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* this functions either returns (when we are in the parent process, i.e. 
 * when *parent == true, OR exits when we are in a child process (*parent ==
 * false), when an error occurs during expansion, file opening, creation of
 * argv and envp or finding of the path for exec
 */
void	return_or_exit(t_env *env, bool *parent)
{
	if (*parent == true)
		return ;
	clear_env(env);
	exit(ms_exit);
}

/* this function is called when we reach an exec node that is not a builtin
 * while we are still in a parent process (*parent == true). In this case,
 * we have to fork. (Otherwise the forking is done in the pipe node)
 */
void	runexecfork(char *path, char **argv, char **envp)
{
	int	pid;
	int	status;

	pid = fork1();
	if (pid ==  0)
	{
		ms_sig_dfl(env);
		execve(path, argv, envp);
		perror(argv[0]);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ms_exit = WEXITSTATUS(status);
}

/* makes and expands argv, makes envp from the env struct. Checks if the 
 * command is a builtin, if so, runs it and then exits (if we are in child
 * process) or returns (when we are in parent process).
 * If the command is not a builtin, calles execve in case we are already in 
 * a child process. Otherwise calls runexecfork that generates a child
 * process.
 */
void	runexec(struct cmd *cmd, t_env *env, bool *parent)
{
	struct execcmd	*ecmd;
	char			**argv;
	char			**envp;
	char			*path;

	ecmd = (struct execcmd *) cmd;
	if (ecmd->argv[0] == NULL)
		return (return_or_exit(env, parent));
	argv = expander(ecmd->argv, env, true, true);
	if (builtin(argv, env))
		return (return_or_exit(env, parent));
	envp = make_envp(env);
	path = find_path(argv[0], env, parent);
	if (envp == NULL || path == NULL)
		return (return_or_exit(env, parent));
	if (*parent == true)
	{
		runexecfork(path, argv, envp);
		return (return_or_exit(env, parent));
	}
	execve(path, argv, envp);
	perror(argv[0]);
	exit(errno);
}

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
	runcmd(rcmd->cmd, env, parent);
	close(file_fd);
	dup(fd_cpy);
}

/* see file heredoc.c
 */
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
	return (return_or_exit(env, parent));
	dprintf(2, "end\n");
}
