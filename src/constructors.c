#include "minishell.h"

struct cmd	*execcmd(void)
{
	struct execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return (struct cmd *)cmd;
}

struct cmd	*redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	struct redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return (struct cmd*)cmd;
}

struct cmd	*pipecmd(struct cmd *left, struct cmd *right)
{
	struct pipecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return (struct cmd*)cmd;
}

struct cmd	*listcmd(struct cmd *left, struct cmd *right)
{
	struct listcmd *cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;
	return (struct cmd*)cmd;
}

/*added by me:*/
struct cmd	*backcmd(struct cmd *subcmd)
{
	struct backcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = BACK;
	cmd->cmd = subcmd;
	return (struct cmd*)cmd;
}

struct cmd	*herecmd(struct cmd *subcmd, char *limit, char *elimit)
{
	struct herecmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = HERE;
	cmd->limit = limit;
	cmd->elimit = elimit;
	cmd->cmd = subcmd;
	return (struct cmd*)cmd;
}

