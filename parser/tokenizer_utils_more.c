/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_more.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:29:33 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/16 10:55:42 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* initializes the structure of a token and sets all 
values to NULL */
void	init_token(t_token **token)
{
	*token = malloc(sizeof(t_token));
	if (!(*token))
	{
		perror("Token not created");
		return (NULL);
	}
	(*token)->input_len = 0;
	(*token)->input = NULL;
	(*token)->type = T_UNKNOWN;
	(*token)->line = NULL;
}

/* initializes the structure of a lexer and sets all 
values to NULL */
void	init_buffer(t_lexer *lexer)
{
	lexer->tokens = malloc(1024);
	if (!lexer->tokens)
		return ;
	lexer->len = 1024;
	lexer->index = 0;
}
