#include "minishell.h"

// Never returns
void	runcmd(struct cmd *cmd, t_env *env)
{
	int	p[2];
	//int	real_stdout;
	char	*line;
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
			argv_expanded = expander(ecmd->argv, env);
			//dprintf(2, "argv_expanded[0] = %s", argv_expanded[0]);
			execvpe(argv_expanded[0], argv_expanded, env->envp);
			//execvpe(ecmd->argv[0], ecmd->argv, env->envp);
			dprintf(2, "exec %s failed\n", ecmd->argv[0]);
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
				panic("pipe");
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
			dprintf(2, "HERE: limit = %s\n", hcmd->limit);
			if (pipe(p) < 0)
				panic("pipe");
			if (fork1() == 0)
			{
				close(p[0]);
				while (1)
				{
					dprintf(1, "pipe heredoc > ");
					line = get_next_line(0);
					len = strlen(line);
					//dprintf(2, "%s", line);
					if (line == NULL)
						break ;
					line[len - 1] = '\0';
					if (strcmp(line, hcmd->limit) == 0)
					{
					//	dprintf(2, "line is limit, break!");
						break ;
					}
					//else 
					//	dprintf(2, "strcmp(line, hcdm->limt) = %d\n", strcmp(line, hcmd->limit));
					write(p[1], line, strlen(line));
					write(p[1], "\n", 1);
					free(line);
				}
				close(p[1]);
				exit(0);
			}
			close(p[1]);
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
			panic("runcmd");
	}
	exit(0);
}
