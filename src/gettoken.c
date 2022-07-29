#include "minishell.h"

char	whitespace[] = " \t\r\n\v";
char	symbols[] = "<|>&;()";

int	gettoken_single_quotes(char **ps, char *es, char **q, char **eq)
{
	char	*s;

	s = *ps;
	if (q)
		*q = s;
	while (*s != '\'')
		s++;
	s++;
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(whitespace, *s))
		s++;
	*ps = s;
	return ('a');
}
		
int	gettoken_double_quotes(char **ps, char *es, char **q, char **eq)
{
	char	*s;

	s = *ps;
	if (q)
		*q = s;
	while (*s != '\"')
		s++;
	s++;
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(whitespace, *s))
		s++;
	*ps = s;
	return ('a');
}

// ps points to begin of the scan, es to the end of the scan,
// q points to begin of the token, eq to end of token.
int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int	ret;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	if (*s == '\'')
	{
		*ps = s;
		return (gettoken_single_quotes(ps, es, q, eq));
	}
	if (*s == '\"')
	{
		*ps = s;
		return (gettoken_double_quotes(ps, es, q, eq));
	}
	if (q)
		*q = s;
	ret = *s;
	//dprintf(2, "gettoken 18, ret = %c\n", ret);
	switch(*s)
	{
		case 0:
			break ;
		case '|':
		case '(':
		case ')':
		case ';':
		case '&':
		case '<':
			s++;
			if (*s == '<')
			{
				ret = '-';
				s++;
			}
			break ;
		case '>':
			s++;
			if (*s == '>')
			{
				ret = '+';
				s++;
			}
			break ;
		default:
			ret = 'a';
			while (s < es && !strchr(whitespace, *s) && !strchr(symbols, *s))
				s++;
			break ;
	}
	//dprintf(2, "45, ret = %c\n", ret);
	if (eq)
		*eq = s;
	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	//dprintf(2, "51, ret = %c\n", ret);
	return (ret);
}

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return *s && strchr(toks, *s);
}

// 48.32 "Shell Code -- More Detail
