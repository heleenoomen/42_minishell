/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 08:32:38 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/01 17:13:06 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

char	get_charbychar(t_prompt *line)
{
	char	c;

	if (line == NULL || line->input == NULL)
		return (CHAR_ERR);
	if (line->index == -2)
		line->index = -1;
	if (line->index + 1 >= line->len)
	{
		line->index = line->len;
		return (EOL);
	}
	c = line->input[line->index];
	return (c);
}

char	set_peek(t_prompt *line)
{
	char	c;
	long	index;

	if (line == NULL || line->input == NULL)
		return (CHAR_ERR);
	index = line->index;
	if (index == -2)
		index++;
	if (index >= line->len)
		return (EOL);
	c = line->input[index];
	return (c);
}

void	update_char(t_prompt *line)
{
	if (line->index < 0)
		return ;
	else
		line->index--;
}

void	skip_whitespace(t_prompt *line)
{
	char	c;

	if (line == NULL || line->input == NULL)
		return ;
	c = set_peek(line);
	while (c != EOL && (c == ' ' || c == '\t'))
		get_charbychar(line);
}
