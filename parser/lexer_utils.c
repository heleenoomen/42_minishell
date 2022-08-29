/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:07:44 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/24 11:04:37 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* frees the content of the token structure and token itself */
void	delete_token(void *token)
{
	if (((t_token *)token)->input)
		free(((t_token *)token)->input);
	free(token);
}

void	flag_exists(int flag)
{
	if (!flag)
	{
		perror("Not enough quotes");
		exit(1);
	}
}

/* checks if line string contains double/single quotes that a complete,
returns flag status, exits if flag returns false*/
int	quote_checker(char *line)
{
	int	quote;
	int	dquote;
	int	complete;

	quote = 0;
	dquote = 0;
	complete = 1;
	while (line && *line)
	{
		if (*line == '\'' && !dquote)
		{
			quote = !quote;
			complete = !complete;
		}
		if (*line == '\"' && !quote)
		{
			dquote = !dquote;
			complete = !complete;
		}
		line++;
	}
	flag_exists(complete);
	return (complete);
}

void	lexer_get_value(t_lexer *lex, t_prompt *line)
{
	int		quote;
	int		dquote;
	char	c;

	quote = 0;
	dquote = 0;
	c = get_charbychar(line);
	if (c == CHAR_ERR || c == EOL)
		return ;
	while (c != EOL)
	{
		if (dquote == 0 && c != '\0' && c == '\'')
			quote = !quote;
		else if (quote == 0 && c != '\0' && c == '\"')
			dquote = !dquote;
		else if (!quote && !dquote)
		{
			if (update_lexer(lex, line, c) == 1)
				break ;
		}
		if (quote || dquote || c == '\'' || c == '\"')
			save_to_lexer(lex, c);
		c = get_charbychar(line);
	}
}
