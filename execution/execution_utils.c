/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 19:50:25 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/02 19:53:37 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

char	*remove_quotes(char *str)
{
	char	*removed;
	int		len;

	len = 0;
	if (str)
	{
		len = ft_strlen(str);
		if ((str[0] == '\"' || str[0] == '\''))
			removed = ft_substr(str, 1, len - 2);
		else
			removed = ft_strdup(str);
	}
	else
		removed = NULL;
	return (removed);
}
