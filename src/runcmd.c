#include "minishell.h"
// Never returns
int	get_argc(char **argv)
{
	int	argc;

	argc = 0;
	while (argv[argc] != NULL)
		argc++;
	return (argc);
}
		
int	builtin(char **argv, t_env *env)
{
	int	argc;

	argc = get_argc(argv);
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		mini_echo(argc, argv);
	else if (ft_strncmp(argv[0], "cd", 3) == 0)
		mini_cd(argc, argv, env);
	else if (ft_strncmp(argv[0], "env", 4) == 0)
		mini_env(env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		mini_unset(argv, env);
	else
		return (0);
	argc = 0;
	while (argv[argc] != NULL)
	{
		free(argv[argc]);
		argc++;
	}
	free(argv);
	return (1);
}

void	runcmd(struct cmd *cmd, t_env *env)
{
	int	p[2];
	//int	real_stdout;
	char	*line;
	char	*path;
	int	len;
	char	**argv_expanded;
	struct backcmd	*bcmd;
	struct execcmd	*ecmd;
	struct listcmd	*lcmd;
	struct pipecmd	*pcmd;
	struct redircmd	*rcmd;
	struct herecmd	*hcmd;

//	dprintf(2, "runcmd\n");
	if (cmd == 0)
		exit(1);

	switch(cmd->type)
	{

		case EXEC:
			//dprintf(2, "EXEC in runcmd");
			ecmd = (struct execcmd*)cmd;
			if (ecmd->argv[0] == 0)
				exit(1);
			argv_expanded = expander(ecmd->argv, env, true, true);
			if (builtin(argv_expanded, env))
			{
			//	dprintf(2, "I'm inside builtin statement\n");
				exit(ms_exit);
			}
			path = find_path(argv_expanded[0], env);
			execve(path, argv_expanded, env->envp);
			//execvpe(ecmd->argv[0], ecmd->argv, env->envp);
			perror(argv_expanded[0]);//d>printf(2, "exec %s failed\n", argv_expanded[0]);
			break;

		case REDIR:
			rcmd = (struct redircmd*)cmd;
			close(rcmd->fd);
			if (open(rcmd->file, rcmd->mode) < 0)
			{
				dprintf(2, "open %s failed\n", rcmd->file);
				exit(1);
			}
			runcmd(rcmd->cmd, env);
			break;

		case LIST:
			lcmd = (struct listcmd*)cmd;
			if (fork1() == 0)
				runcmd(lcmd->left, env);
			wait(0);
			runcmd(lcmd->right, env);
			break;

		case PIPE:
			pcmd = (struct pipecmd*)cmd;
			if (pipe(p) < 0)
				panic("pipe", NULL);
			if (fork1() == 0)
			{
		//		dprintf(2, "run left cmd");
				close(1);
				dup(p[1]);
				close(p[0]);
				close(p[1]);
				runcmd(pcmd->left, env);
			}
			if (fork1() == 0)
			{
		//		dprintf(2, "run right cmd");
				close(0);
				dup(p[0]);
				close(p[0]);
				close(p[1]);
				runcmd(pcmd->right, env);
			}
			close(p[0]);
			close(p[1]);
			wait(0);
			wait(0);
			break ;

		case HERE:
			hcmd = (struct herecmd*)cmd;
			//dprintf(2, "HERE: limit = %s\n", hcmd->limit);
			if (pipe(p) < 0)
				panic("pipe", NULL);
			if (fork1() == 0)
			{
				close(p[0]);
				while (1)
				{
//					dprintf(1, "pipe heredoc > ");
					line = readline("pipe heredoc > ");
			//		line = get_next_line(0);
					len = strlen(line);
					//dprintf(2, "%s", line);
					if (line == NULL)
					{
						dprintf(2, "line is NULL");
						break ;
					}
					//line[len - 1] = '\0';
					if (strcmp(line, hcmd->limit) == 0)
					{
					//	dprintf(2, "line is limit, break!");
						break ;
					}
					//else 
					//	dprintf(2, "strcmp(line, hcdm->limt) = %d\n", strcmp(line, hcmd->limit));
//					dprintf(2, "line is: %s\n", line);
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
				close(0);
				dup(p[0]);
				close(p[0]);
				runcmd(hcmd->cmd, env);
			}
			close(p[0]);
			wait (0);
			break ;
		case BACK:
			bcmd = (struct backcmd*)cmd;
			if ((fork1()) == 0)
				runcmd(bcmd->cmd, env);
			break;
		default:
			panic("runcmd", NULL);
	}
	exit(0);
}
