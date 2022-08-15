/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:58:11 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/15 21:57:17 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* After saving string into the node of AST, frees the token input that was 
allocated before*/

void	free_token(void *token)
{
	if (((t_token *)token)->input)
		free(((t_token *)token)->input);
	free(token);
}

/* Initializes the prompt structure by saving the input line */
void	init_content(t_prompt *content, char *input)
{
	content->input = ft_strdup(input);
	content->len = ft_strlen(input);
	content->index = -2;
}
