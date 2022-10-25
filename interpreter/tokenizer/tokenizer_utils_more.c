/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils_more.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:29:33 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/14 13:20:14 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* initializes the structure of a token and sets all 
values to NULL */
t_token	*init_token(void)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
	{
		error_shell("Token not initialized", ERROR_PERROR);
		return (NULL);
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
