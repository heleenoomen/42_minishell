/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:30:14 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/09 14:57:23 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	init_buffer(t_lexer *lexer)
{
	lexer->len = 1024;
	lexer->tokens = malloc(lexer->len);
	if (!lexer->tokens)
		return ;
}

char	*increase_buffer(void *temp1, int current_size, int update_size)
{
	void	*temp2;

	temp2 = NULL;
	if (current_size < update_size)
	{
		temp2 = malloc(update_size);
		if (temp2 == NULL)
			return (NULL);
		if (temp1 != NULL)
		{
			ft_memcpy(temp2, temp1, current_size);
			free(temp1);
		}
	}
	else
		temp2 = temp1;
	return (temp2);
}

void	save_buffer(t_lexer *lex, char c)
{
	void	*temp;

	temp = NULL;
	lex->tokens[lex->index++] = c;
	if (lex->index >= lex->len)
	{
		temp = increase_buffer(temp, lex->len, lex->len * 2);
		if (temp == NULL)
			return ;
		lex->tokens = (char *)temp;
		lex->len *= 2;
	}
}

void	token_operator(t_lexer *lex, t_prompt *line, char c)
{
	char	peek;

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
		else if (lex->index > 0)
			update_char(line);
		else
			save_buffer(lex, c);
	}
}

int	update_buffer(t_lexer *lex, t_prompt *line, char c)
{
	int	found;

	found = 0;
	if (c == ' ' || c == '\t')
	{
		if (lex->index > 0)
			found = 1;
	}
	else if (c == '\n' || c == '|' || c == '>' || c == '<')
	{
		token_operator(lex, line, c);
		found = 1;
	}
	else
		save_buffer(lex, c);
	return (found);
}

int	check_value_assign(char *str)
{
	int	i;
	int	flag;

	if (str == NULL)
		return (0);
	i = 1;
	flag = 1;
	if (str[0] != '_' && ft_isalpha(str[0] == 0))
		flag = 0;
	while (flag == 1 && str[i])
	{
		if (str[0] != '_' && ft_isalnum(str[i] == 0))
			flag = 0;
		i++;
	}
	return (flag);
}

void	get_token_type(t_token *token, char *lex)
{
	if (ft_strcmp(lex, "|") == 0)
		token->type = T_PIPE;
	else if (ft_strcmp(lex, ">") == 0)
		token->type = T_GREAT;
	else if (ft_strcmp(lex, "<") == 0)
		token->type = T_LESS;
	else if (ft_strcmp(lex, ">>") == 0)
		token->type = T_DGREAT;
	else if (ft_strcmp(lex, "<>") == 0)
		token->type = T_LESSGREAT;
	else if (ft_strcmp(lex, "<<") == 0)
		token->type = T_DLESS;
	else if (ft_strcmp(lex, "=" && check_value_assign(lex) == 0) == 0)
		token->type = T_ASSIGN;
	else
		token->type = T_STRING;
}

void	parser(t_lexer *lex, t_prompt *line)
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
		if (dquote == 0 && c == '\'' && c != '\0')
			quote = 1;
		else if (quote == 0 && c == '\"' && c != '\0')
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
	token->line = lex;
	return (token);
}

t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("Token not created");
		return (NULL);
	}
	token->input_len = 0;
	token->input = NULL;
	token->type = T_UNKNOWN;
	token->line = NULL;
}

t_token	*tokenizer(t_lexer *lex, t_prompt *line)
{
	t_token	*token;

	token = init_token();
	if (line == NULL || line->input == NULL || token->len == 0)
	{
		token = launch_tokens(token, line, NULL);
		return (token);
	}
	if (lex->tokens == NULL)
		init_buffer(lex);
	if (lex->tokens == NULL)
	{
		token = launch_tokens(token, line, NULL);
		return (token);
	}
	lex->index = 0;
	lex->tokens[0] = '\0';
	parser(lex, line);
	if (lex->index == 0)
	{
		token = launch_tokens(token, line, NULL);
		return (token);
	}
	if (lex->index >= lex->len)
		lex->index--;
	lex->tokens[lex->index] = '\0';
	if (token != NULL)
		token = launch_tokens(token, line, lex->tokens);
	return (token);
}
