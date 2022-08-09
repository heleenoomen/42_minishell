#ifndef CMDS_H
# define CMDS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include "get_next_line.h"

# define EXEC	1
# define REDIR	2
# define PIPE	3
# define LIST	4
# define BACK	5
# define HERE	6

# define MAXARGS 10

struct cmd
{
	int	type;
};

struct execcmd
{
	int	type;
	int	argc;
	int	quote_modus;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
};

struct redircmd
{
	int		type;
	int		quote_modus;
	struct cmd	*cmd;
	char		*file;
	char		*efile;
	int		mode;
	int		fd;
};

struct pipecmd
{
	int		type;
	struct cmd	*left;
	struct cmd	*right;
};

struct listcmd
{
	int		type;
	struct cmd	*left;
	struct cmd	*right;
};

struct backcmd 
{
	int		type;
	struct cmd	*cmd;
};

struct herecmd
{
	int		type;
	int		quote_modus;
	char		*limit;
	char		*elimit;
	struct cmd	*cmd;
};

/*constructors.c*/
struct cmd		*execcmd(void);
struct cmd		*redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd);
struct cmd		*pipecmd(struct cmd *left, struct cmd *right);
struct cmd		*listcmd(struct cmd *left, struct cmd *right);
struct cmd		*backcmd(struct cmd *subcmd);
struct cmd		*herecmd(struct cmd *subcmd, char *limit, char *elimit);

/*gettoken2.c*/
int			gettoken(char **ps, char *es, char **q, char **eq);
int			peek(char **ps, char *es, char *toks);

/*main.c*/
void			panic(char *s);
int			fork1(void);

/*parsecmd.c*/
struct cmd		*parseexec(char **ps, char *es);
struct cmd		*parseredirs(struct cmd *cmd, char **ps, char *es);
struct cmd		*parsepipe(char **ps, char *es);
struct cmd		*parseline(char **ps, char *es);
struct cmd		*parseblock(char **ps, char *es);
struct cmd		*parsecmd(char *s);
void			nulterminate(struct cmd *cmd);

/*runcmd.c*/
void			runcmd(struct cmd *cmd, t_env *env);
#endif
