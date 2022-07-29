#include "minishell.h"

// Never returns
void	runcmd(struct cmd *cmd)
{
	int	p[2];
	//int	real_stdout;
	char	*line;
	int	len;
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
			execvp(ecmd->argv[0], ecmd->argv);
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
			runcmd(rcmd->cmd);
			break;

		case LIST:
			lcmd = (struct listcmd*)cmd;
			if (fork1() == 0)
				runcmd(lcmd->left);
			wait(0);
			runcmd(lcmd->right);
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
				runcmd(pcmd->left);
			}
			if (fork1() == 0)
			{
		//		dprintf(2, "run right cmd");
				close(0);
				dup(p[0]);
				close(p[0]);
				close(p[1]);
				runcmd(pcmd->right);
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
					free(line);
				}
				exit(0);
			}
			close(p[1]);
			wait (0);
			if (fork1() == 0)
			{
				close(0);
				dup(p[0]);
				close(p[0]);
				runcmd(hcmd->cmd);
			}
			close(p[0]);
			wait (0);
			break ;
		case BACK:
			bcmd = (struct backcmd*)cmd;
			if ((fork1()) == 0)
				runcmd(bcmd->cmd);
			break;
		default:
			panic("runcmd");
	}
	exit(0);
}
