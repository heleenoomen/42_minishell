/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 14:47:46 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/21 14:48:27 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* this header file was what I used for my version of minishell. It can be dis-
 * carded, but it might help you if you want to read my versio of the execution
 * files
 */

#ifndef CMDS_H
# define CMDS_H

# define EXEC	1
# define REDIR	2
# define PIPE	3
# define LIST	4
# define BLOCK	5
# define HERE	6
# define AND	7
# define OR		8

struct cmd
{
	int	type;
};

struct execcmd
{
	int		type;
	int		argc;
	int		quote_modus;
	char	*argv[ARGS];
	char	*eargv[ARGS];
	int		free;
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
struct cmd		*blockcmd(struct cmd *subcmd);
struct cmd		*herecmd(struct cmd *subcmd, char *limit, char *elimit);

/*gettoken2.c*/
int			gettoken(char **ps, char *es, char **q, char **eq);
int			peek(char **ps, char *es, char *toks);

/*main.c*/
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
void			runcmd(struct cmd *cmd, t_env *env, bool *parent);
#endif
