char whitespace[] = " \t\r\n\v";
char symbols[] = "<|>;()";

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	switch (*s){
		case 0:
			break ;
		case '|':
		case '(':
		case ')':
		case ';':
		case '&':
		case '<':
			s++;
			break ;
		case '>':
			s++;
			if (*s == '>'){
				return '+'; // this is the return value when token is >>
				s++;
			}
			break ;
		default:
			ret = 'a' // this is the return value for a 
			while (s < es && !strchr(whitespace, *s) && !strchr(symbols)
				s++;
			break ;
	}
	if (eq)
		*eq = s;
	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s; // next time we call gettoken, we will start from here
	return ret;
}

// peek looks past any whitespace character and finds te next non-whitespace char. It is a boolean. It checks whether the next non-whitespace char is one of the toks or not.
int	peek(char **ps, char **es, char *toks)
{
	char *s;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return *s && strchr(toks, *s); // if it's not the nul character and one of the chars in the set of chars toks, then we return 1, otherwise 0.
}

struct cmd	*parsecmd(char *s)
{
	char		*es;
	struct cmd *cmd;

	es = s + strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");  // peek looks for leftovers after the end of string
	if (s != es){
		fprintf(2, "leftovers: %s\n", s);
		panic("syntax");
	}
	nulterminate(cmd); // nulterminate walks the tree again to nullterminate allcommands/options/filenames with \0
	return (cmd);

/* parseline and all the other functions that do the recursive descent parsing:
 *
 *	parseexec: EXEC
 * 				REDIR { aaa REDIR } 
 * 				( BLOCK
 * 			// this is the leave node. aaa is at least one token (program name) 				and one or more options. parseexec will either see REDIR or aaa 				OR it wil see a parenthesis and call block. It doesn't scan it, 				it only sees it (peek) and if it sees it it calls block. If it d				doesn't see a parenthesis, it goes on to do the first line. 
 * 			
 * 	parseredirs: REDIR
 * 					{ < aaa } 
 * 					{ > aaa }
 * 					{ >> aaa}
 * 					{ << aaa} 
 * 				// aaa will be a filename, there can be zero or more
 *
 *	parsepipe: PIPE
 *				EXEC [ | PIPE ]
 *			//parsepipe calls parseexec. It will then parse a pipe and call itse				lf recursively. (the square brackets indicate that there may be 
 *				zero or more pipes. If there are no pipes, pipe will not call it				itself recursively
 *	
 *	parseline: LINE
 *				PIPE {&} [; LINE]  //{} indicate: zero or more
 *			//it calls parsepipe first, than parses zero, one or two ampersands,				 and then, if it finds a semicolon, calles parseline (itself, re				cursively)
 *
 * 	parseblock: BLOCK
 * 				(LINE) REDIR
 * 			//parseblock reads in a left parenthesis, then recursively call
 *				the function parseline. After that line has been parsed, it
 *				scans the right parenthesis and then calls the function that
 *				parses redirections.
 *
 *
 *
 * The parsepipe builds a right recursive tree:
 * 	so that aaa | bbb | ccc | ddd  
 * 			will look like:
 *
 * 					PIPE
 *					/  \
 *				EXEC	PIPE
 *				aaa		/  \
 *					EXEC	PIPE
 *					bbb		/  \
 *						EXEC	PIPE
 *						ccc		 | 
 *								EXEC
 *								ddd	
 *	
 *	in other words, parsepipe either calls parseexec and if it finds no further 	pipe or it calls execparse and then calls itself
 *
 * 
 * The goal of each of the above functions is to build the tree.
 */
 
/* Notations:
 * {} means: one or more
 * {}+ means: zero or more
 * {}* means also: one or more
 */
	
	
struct cmd	*parsepipe(char **ps, char **es) // ps and es refer to the input buffer
{
	struct cmd	*cmd;

	cmd = parseexec(ps, es, "|"); // this builds a tree
	if (peek(ps, es, "|")){
		gettoken(ps, es, 0, 0); // we pass null pointers
		cmd = pipecmd(cmd, parsepipe(ps, es)); // this is the pipenode construction function. It is passed a poointer to the left (cmd) and a pointer to the right that will be returned by parsepipe.
	}
	return cmd;
}

struct cmd *parseline(char **ps, char **es) // ps is current position in input
{
	struct cmd	*cmd;

	cmd = parsepipe(ps, es);
	while (peek(ps, es, "&")){
		gettoken(ps, es, 0, 0);
		cmd = backcmd(cmd);
	}
	if (peek(ps, es, ";")){
		gettoken(ps, es, 0, 0);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	return (cmd);
}

struct cmd	*parseblock(char **ps, char **es)
{
	struct cmd	*cmd;

	if (!peek(ps, es, "(") // we now for sure, because parseexec only calls this function after peeking if there is indeed a (. This is therefore nothing more than a quick (and possible redundant) error check
		panic("parseblock");
	gettoken(ps, es, 0, 0);
	cmd = parseline(ps, es);
	if (!peek(ps, es, ")"))
		painc("syntax - missing )");
	gettoken(ps, es, 0, 0);
	cmd - parseredirs(cmd, ps, es); // we pass a tree that we have build up so far, this will possibly add a new root. 
	return (cmd);
}

//this adds a root to existing tree.
struct cmd *parseredirs(struct cmd *cmd, char **ps, char **es)
{
	int	tok;
	char *q;

	while (peek(ps, es, "<>")){
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
			panic("missing file for redirection");
		switch (tok){
		case '<':
			cmd = redircmd(cmd, q, eq, O_RDONLY, 0); // pointers to filename and end of filename. The filedescriptor is the last parameter. 0 = stdin, 1 = stdout
			break ;
		case '>':
			cmd = redircmd(cmd, q, es, O_WRONLY | O_CREATE | O_TUNCATE);
			break ;
		case '+': // >>
			cmd = redircmd(cmd, q, eq, O_WRONLY | O_CREATE, 1);
			break ;
		}
	}
}

struct cmd	*parseexec(char **ps, char *es)
{
	char			*q;
	char			*eq;
	int				tok;
	int				argc;
	struct execcmd	*cmd;
	struct cmd		*ret; // this refers to the tree that we have build so far

	if (peek(ps, es, "("))
		return (parseblock(ps, es);
	
	ret = execcmd(); // this allocates the node, doesn't fill it in yet.
	cmd = (struct execcmd*)ret;

	argc = 0;
	ret = parseredirs(ret, ps, es); // we pass it the tree that we build so far
	// this tree now contains only the execcmd node that we just created, not ev	// even filled in yet. parsedirs allocates a REDIR node, with a pointer to b	// beginning of filename and end of filename, the mode, filedescriptor and a
	// pointer to the subtree, that is our empty execnode that we just created.
	while (!peek(ps, es, "|)&;")){  // check if it's not any of these
		if ((tok = gettoken(ps, es, &q, &eq)) == 0)  // end of string
			break ;
		if (tok != 'a')  // now it should be a name (cmd, option, filename)
			panic("syntax");
		cmd->argv[argc] = q; // beginning of token
		cmd->eargv[argc] = eq; // (end of token) 
		argc++;
		if (argc >= MAXARGS) // check if there are not too many elements/options
			panic("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = NULL;
	cmd->eargv[argc] = NULL;
	return ret;
}

/* what we might encounter in program:
 * 	pgm opt1 opt2 <file1 >file2    (typical format)
 * 	<file1 pgm op1 >file2			(this is also possible, it works also)
 * 	
 * 	either will be handled in the same way

 * the EXEC node looks like this:
 *
 * 	     ------
 * type  |EXEC|
 * 	     ------
 * 	     |    |    argv and argc are fixed size arrays of pointers
 * argv  |    |
 * 	     |    |
 * 	     ------
 * 	     |    |
 * eargv |    |
 * 	     |    |
 * 	     ------
 *
 * the REDIR node looks like this:
 *
 * 		 -------
 * 		 |REDIR|
 * 		 -------
 * 		 |     | ptr to beginning of filename
 * 		 -------
 * 		 |     | ptr to end of filename
 * 		 -------
 * 		 |     | modus (O_WRONLY, O_TRUNC etc.)
 * 		 -------
 *		 |     | filedescriptor STDIN or STDOUT that it's going to redirect
 *		 -------
 *		 |     | pointer to subtree (EXEC node)
 *		 -------
/*
 */

struct *cmd
