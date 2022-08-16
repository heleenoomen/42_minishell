/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:07:44 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/16 14:10:14 by ktashbae         ###   ########.fr       */
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
	if (flag == 0)
	{
		perror("Not enough quotes");
		exit(1);
	}
}

/* checks if line strigh contains double/single quotes with special case,
returns flag status, exits if flag returns false*/
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
	flag_exists(flag);
	return (flag);
}
