#include "minishell.h"

struct cmd	*parseexec(char **ps, char *es)
{
	char	*q;
	char	*eq;
	int	tok;
	int	argc;
	struct execcmd	*cmd;
	struct cmd	*ret;

	//dprintf(2, "*ps = %s\n", *ps);
	if (peek(ps, es, "("))
		return parseblock(ps, es);
	
	ret = execcmd();
	cmd = (struct execcmd*)ret;

	argc = 0;
	ret = parseredirs(ret, ps, es);
	while (!peek(ps, es, "|)&;"))
	{
		tok = gettoken(ps, es, &q, &eq);
		//dprintf(2, "24, tk = %d\n", tok);
		if (tok == 0)
			break ;
		//dprintf(2, "26, tok = %d\n", tok);
		if (tok != 'a')
			panic("syntax 26");
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (argc >= MAXARGS)
			panic("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argc = argc;
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	//dprintf(2, "%d\n", cmd->type);
	return ret;
}

struct cmd *parseredirs(struct cmd *cmd, char **ps, char *es)
{
	int	tok;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
		{
			if (tok != '-')
				panic("missing file for redirection");
			else
				panic("heredoc: missing delimiter");
		}
		switch(tok)
		{
			case '<':
				cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
				break ;
			case '>':
				cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_TRUNC, 1);
				break ;
			case '+':
				cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREAT | O_APPEND, 1);
				break ;
			case '-':
				cmd = herecmd(cmd, q, eq);
		}
	}
	return (cmd);
}

struct cmd	*parsepipe(char **ps, char *es)
{
	struct cmd	*cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
//	dprintf(2, "type at end of parsepipe: %d\n", cmd->type);
//	if (cmd->type == PIPE)
//	{
//		struct pipecmd *pcmd = (struct pipecmd *)cmd;
//		dprintf(2, "type left branch: %d\n", pcmd->left->type);
//		dprintf(2, "type right branch: %d\n", pcmd->right->type);
//	}
	return cmd;
}

struct cmd	*parseline(char **ps, char *es)
{
	struct cmd	*cmd;

	cmd = parsepipe(ps, es);
	while (peek(ps, es, "&"))
	{
		gettoken(ps, es, 0, 0);
		cmd = backcmd(cmd);
	}
	if (peek(ps, es, ";"))
	{
		gettoken(ps, es, 0, 0);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	//dprintf(2, "parseline, cmd->type = %d\n", cmd->type);
	return cmd;
}

struct cmd	*parseblock(char **ps, char *es)
{
	struct	cmd *cmd;

	if (!peek(ps, es, "("))
		panic("parseblock");
	gettoken(ps, es, 0, 0);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
		panic("sytanx - missing )");
	gettoken(ps, es, 0, 0);
	cmd = parseredirs(cmd, ps, es);
	return cmd;
}

struct cmd	*parsecmd(char *s)
{
	char	*es;
	struct cmd	*cmd;

	es = s + strlen(s);
	cmd = parseline(&s, es);
//	dprintf(2, "parsecmd, cmd->type = %d\n", cmd->type);
	peek(&s, es, ""); // by "" he possibly means \0 char, (14.12) in "Shell Code -- More Detail"//
	if (s != es)
	{
		dprintf(2, "leftovers: %s\n", s);
		panic("syntax error");
	}
//	dprintf(2, "parsecmd before nulterminate, cmd->type = %d\n", cmd->type);
	nulterminate(cmd);
//	dprintf(2, "parsecmd after nulterminate, cmd->type = %d\n", cmd->type);
	return cmd;
}

void	nulterminate(struct cmd *cmd)
{
	int		i;
	struct execcmd	*ecmd;
	struct redircmd	*rcmd;
	struct pipecmd	*pcmd;
	struct herecmd	*hcmd;
	//struct listcmd	*lcmd;
	//struct backcmd	*bcmd;

	if (cmd->type == EXEC)
	{
		ecmd = (struct execcmd *)cmd;
		i = 0;
		while (ecmd->eargv[i] != NULL)
		{
			*(ecmd->eargv[i]) = '\0';
			i++;
		}
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (struct redircmd *)cmd;
		*(rcmd->efile) = '\0';
		nulterminate(rcmd->cmd);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (struct pipecmd *)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
	}	
	else if (cmd->type == HERE)
	{
		hcmd = (struct herecmd *)cmd;
		*(hcmd->elimit) = '\0';
		nulterminate(hcmd->cmd);
	}
}



