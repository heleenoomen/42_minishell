/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:26:37 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/21 14:27:43 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* possible structure for execution of exec type nodes */

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
