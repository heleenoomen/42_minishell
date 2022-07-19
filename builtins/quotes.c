/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 15:45:52 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/19 16:21:43 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"



bool	is_valid_key(char **s, char **value, int *quotes)
{
	char	*ptr;
	char	*key;

	ptr = *s;
	key = *s;
	*quotes = NO_QUOTES
	if (*ptr == '\'')
		*quotes = SINGLE_QUOTES
	else if (*ptr == '\"')
		*quotes = DOUBLE_QUOTES
	else if (!ft_isalpha(*ptr) && *ptr != '_')
		return (false);
	else
		**key = *ptr;
	ptr++;
	while (*ptr != '=')
	{
		if (ft_isalnum(*ptr) || *ptr == '_')
		{
			*key = *ptr;
			key++;
		}
		else if (*ptr == '\"' || *ptr == '\'')
			quotes_key(&ptr, quotes);
		else
			return (false);
		ptr++;
	}
	*key = '\0';
	*value = key + 1;
	return (true);
}

