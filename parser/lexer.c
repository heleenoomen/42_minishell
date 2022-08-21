/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 09:15:57 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/16 14:10:17 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* checks for token, if pipe, and, or operators are found it sets cmd value to zero,
if type is string - recognized as cmd. If previous type was string, current assignment
is changed into type string */
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

/* loops over the lexer and adds token structure into
the linked list. In case of, check flag failure, it cleans the list */
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

/*
initializes the structure of a lexer and sets all 
values to NULL. It has:
- token as a string;
- length af a token;
- index of current position.
 */
void	init_lexer(t_lexer *lex)
{
	lex->tokens = NULL;
	lex->len = 0;
	lex->index = -1;
}

/*
creates a structure for lexer, gets a list of tokens retrieved char by char
the input line and returns a list of tokens
*/
t_list	*lexer(t_prompt *line)
{
	t_list	*tokens;
	t_lexer	lex;

	init_lexer(&lexer);
	tokens = get_token_list(&lexer, line);
	free(lex.tokens);
	return (tokens);
}
