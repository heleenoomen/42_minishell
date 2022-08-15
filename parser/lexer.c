/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:15:57 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/02 10:41:28 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int	flag_checker(char *line)
{
	int	quote;
	int	dquote;
	int	flag;
	int	i;

	quote = 0;
	dquote = 0;
	flag = 1;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' && !dquote)
		{
			quote = !quote;
			flag = !flag;
		}
		if (line[i] == '\"' && !quote)
		{
			dquote = !dquote;
			flag = !flag;
		}
		i++;
	}
	if (flag == 0)
	{
		perror("Not enough quotes");
		exit(1);
	}
	return (flag);
}

void	type_checker(t_token *token, int *cmd, int *flag)
{
	if (*flag == 0)
		flag = flag_checker(token->line);
	if (token->type == T_PIPE || token->type == T_AND || token->type == T_OR)
		*cmd = 0;
	if (token->type == T_STRING)
		*cmd = 1;
	if (token->type == T_ASSIGN && *cmd == 1)
		token->type = T_STRING;
}

t_list	*get_token_list(t_lexer *lex, char *line)
{
	int		cmd_found;
	int		check_flag;
	t_list	*token_list;
	t_token	*token;

	cmd_found = 0;
	check_flag = 0;
	token_list = NULL;
	token = tokenizer(lex, line);
	while (token->type != T_EOF)
	{
		type_checker(token, &cmd_found, &check_flag);
		ft_lstadd_back(&token_list, ft_lstnew(token));
		token = tokenizer(lex, line);
	}
	ft_lstadd_back(&token_list, ft_lstnew(token));
	if (check_flag == 1)
		ft_lstclear(&token_list, &delete_token);
	return (token_list);
}

void	run_lexer(t_lexer *lex)
{
	lex->tokens = NULL;
	lex->len = 0;
	lex->index = -1;
}

t_list	*lexer(t_prompt *line)
{
	t_list	*tokens;
	t_lexer	lex;

	run_lexer(&lexer);
	tokens = get_token_list(&lexer, line);
	free(lex.tokens);
	return (tokens);
}
