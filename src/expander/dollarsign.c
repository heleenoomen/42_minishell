/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarsign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:48:03 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 14:27:59 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_substr_ds(t_env *env, t_char_buf *buf, char **ptr)
{
	char	*key;
	char	*end_of_key;
	char	*value;
	char	temp;

	key = *ptr + 1;
	end_of_key = key;
	while (*end_of_key)
	{
		if (ft_strchr(ENDOFVAR, *end_of_key))
			break ;
		end_of_key++;
	}
	temp = *end_of_key;
	*end_of_key = '\0';
	value = find_value(env, key);
	*end_of_key = temp;
	add_str_to_buf(buf, value);
}

bool	should_be_expanded(char **ptr, t_char_buf *buf, int quotes)
{
	char	next_char;

	next_char = *(*ptr + 1);
	if (quotes == SINGLE_QUOTES)
		return (false);
	if (next_char == '\'' || next_char == '\"')
	{
		if (quotes == DOUBLE_QUOTES)
			add_to_buf(buffer, *ptr2);
		(*ptr)++;
		return (false);
	}
	if (next_char == '$')
	{
		add_str_to_buf(buffer, "$$");
		(*ptr) += 2;
		return (false);
	}
	return (true);
}

/* copies string into buffer in t_char_buf struct. Sets the buffer to NULL if
 * malloc fails somewhere along the way. 
 * expands dollar signs when needed (depending on quotes, environment variables
 * and following dollarsigns)
 */
void	expand_dollarsign(t_env *env, char *ptr, t_char_buf *buf)
{
	char		*ret;
	int			quotes;

	init_char_buf(&buf);
	if (buf.buf == NULL)
		return (NULL);
	quotes = NO_QUOTES;
	while (*ptr)
	{
		if (*ptr = '$')
		{
			if (should_be_expanded(&ptr, buf, in_quotes)
				expand_substr_ds(env, buf, &ptr);
		}
		else 
		{
			if (*ptr == '\'' || *ptr == '\"')
				change_quote_modus(&quotes, *ptr);
			add_to_buf(buf, *ptr);
			ptr++;
		}
		if (buf->buf == NULL)
			return ;
	}
}
