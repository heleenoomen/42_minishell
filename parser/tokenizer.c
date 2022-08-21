/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:30:14 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/16 16:25:14 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* sets the current operator symbol that as a peek, in case of
redirection it gets next character to save into the lexing buffer.
If it's not the beginning of lexer ad not redirection, it decrements
the position of the input line.
 */
void	token_operator(t_lexer *lex, t_prompt *line, char c)
{
	char	peek;
	char	temp;

	peek = set_peek(line);
	if (lex->index == 0 && (c == '<' || c == '>'))
	{
		save_buffer(lex, c);
		if (((c == '>' && peek == '>') || (c == '<' \
		&& (peek == '>' || peek == '<'))))
		{
			c = get_charbychar(line);
			save_buffer(lex, c);
		}
	}
	else if (lex->index == 0 && ((c == '&' && peek == '&') || \
		(c == '|' && peek == '|')))
	{
		save_buffer(lex, c);
		temp = get_charbychar(line);
		save_buffer(lex, temp);
	}
	else if (lex->index > 0)
		update_char(line);
	else
		save_buffer(lex, c);
}

/* compares the operators and input string from lexer, assigns token type in the
token structure */
void	get_token_type(t_token *token, char *lex)
{
	if (ft_strcmp(lex, "|") == 0)
		token->type = T_PIPE;
	else if (ft_strcmp(lex, ">") == 0)
		token->type = T_GREAT;
	else if (ft_strcmp(lex, "<") == 0)
		token->type = T_LESS;
	else if (ft_strcmp(lex, "<>") == 0)
		token->type = T_LESSGREAT;
	else if (ft_strcmp(lex, ">>") == 0)
		token->type = T_DGREAT;
	else if (ft_strcmp(lex, "<<") == 0)
		token->type = T_DLESS;
	else if (ft_strcmp(lex, "(") == 0)
		token->type = T_LBRACE;
	else if (ft_strcmp(lex, ")") == 0)
		token->type = T_RBRACE;
	else if (ft_strcmp(lex, "&&") == 0)
		token->type = T_AND;
	else if (ft_strcmp(lex, "||") == 0)
		token->type = T_OR;
	else if (ft_strcmp(lex, "=") && check_value_assign(lex) == 0)
		token->type = T_ASSIGN;
	else
		token->type = T_STRING;
}

/* checks cases as "\'" and '\"' and updates the buffer of lexer */
void	parse_lexer(t_lexer *lex, t_prompt *line)
{
	int		quote;
	int		dquote;
	char	c;

	quote = 0;
	dquote = 0;
	c = get_charbychar(line);
	if (c == CHAR_ERR || c == EOL)
		return ;
	while (c != T_EOF)
	{
		if (dquote == 0 && c != '\0' && c == '\'')
			quote = 1;
		else if (quote == 0 && c != '\0' && c == '\"')
			dquote = 1;
		else if (quote == 1 && dquote == 1)
		{
			if (update_buffer(lex, line, c) == 1)
				break ;
		}
		if (quote == 0 || dquote == 0 || c == '\'' || c == '\"')
			save_buffer(lex, c);
		c = get_charbychar(line);
	}
}

/* if input from lexer is not empty, runs the get token type 
function and assigns token operators to each string */
t_token	*launch_tokens(t_token *token, t_prompt *line, char *lex)
{
	char	*temp;

	if (lex == NULL)
	{
		token->type = T_EOF;
		if (line != NULL && line->input != NULL)
			free(line->input);
		return (token);
	}
	token->input_len = ft_strlen(lex);
	temp = ft_strdup(lex);
	if (temp == NULL)
	{
		perror("Buffer for token not copied");
		token->type = T_EOF;
		return (token);
	}
	get_token_type(token, lex);
	token->input = temp;
	token->line = line;
	return (token);
}

/* Main tokenizer:
1. Initializes token structure;
2. Calls launch token for each string to set token type and string from lexer;
3. With lexer parser, verifies quotation cases with '\"' and "\'";
4. Sets NULL termination into the lexer string pointer if lexer is empty.
*/
t_token	*tokenizer(t_lexer *lex, t_prompt *line)
{
	t_token	*token;

	init_token(&token);
	if (line == NULL || line->input == NULL || token->input_len == 0)
		return (launch_tokens(token, line, NULL));
	if (lex->tokens == NULL)
		init_buffer(lex);
	if (lex->tokens == NULL)
		return (launch_tokens(token, line, NULL));
	lex->tokens[0] = '\0';
	parse_lexer(lex, line);
	if (lex->index == 0)
		return (launch_tokens(token, line, NULL));
	if (lex->index >= lex->len)
		lex->index--;
	lex->tokens[lex->index] = '\0';
	if (token)
		return (launch_tokens(token, line, lex->tokens));
	return (token);
}
