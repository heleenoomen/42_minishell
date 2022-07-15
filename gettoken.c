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
 * 				REDIR { aaa REDIR }+
 *
 *	parsepipe: PIPE
 *				EXEC [ | PIPE ]
 *			//parsepipe calls parseexec. It will then parse a pipe and call itse				lf recursively. (the square brackets indicate that there may be 
 *				zero or more pipes. If there are no pipes, pipe will not call it				itself recursively
 *
 * 	parseblock: BLOCK
 * 				(LINE) REDIR
 * 			//parseblock reads in a left parenthesis, then recursively call
 *				the function parseline. After that line has been parsed, it
 *				scans the right parenthesis and then calls the function that
 *				parses redirections.
 *
