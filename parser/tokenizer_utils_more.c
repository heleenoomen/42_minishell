/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_more.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:29:33 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/23 18:19:35 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* initializes the structure of a token and sets all 
values to NULL */
t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		perror("Token not created");
		exit(1);
	}
	token->input_len = 0;
	token->input = NULL;
	token->type = T_UNKNOWN;
	token->line = NULL;
	return (token);
}

/* initializes the structure of a lexer and sets all 
values to NULL */
void	init_buffer(t_lexer *lexer)
{
	lexer->tokens = malloc(526);
	lexer->len = 526;
	lexer->index = 0;
	if (lexer->tokens == NULL)
		return ;
}
