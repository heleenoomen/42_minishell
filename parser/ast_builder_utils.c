/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:58:11 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/24 11:55:39 by ktashbae         ###   ########.fr       */
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
void	copy_input_line(t_prompt *line, char *readline)
{
	line->input = ft_strdup(readline);
	line->len = ft_strlen(readline);
	line->index = -2;
}
