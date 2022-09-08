/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_filename_expansion_comparison.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:03:52 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/08 19:45:59 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	no_star_part(char *text)
{
	size_t	len;

	len = 0;
	while (text[len] != '*' && text[len] != '\0')
		len++;
	return (len);
}

int	file_list_comparison(char *search, char *files)
{
	char	*match;
	size_t	len_text;

	if (*search == '*')
	{
		while (*search == '*')
			search++;
		if (!*search)
			return (1);
		len_text = no_star_part(search);
		match = ft_substr(search, 0, len_text);
		search = ft_strstr(search, match);
		free(match);
		if (!search)
			return (0);
	}
	while (*files && * search && *search == *files)
	{
		*search++;
		*files++;
	}
	if ((!*search && !*files) || (*search == '*' && *(search + 1) == '\0'))
		return (1);
	if (*search == '*')
		return (file_list_comparison(search, files);
	return (0);
}

int	file_cmp(char *search, char	*files)
{
	int	cmp;

	if (!files || ! search)
		return (0);
	if (ft_strcmp(search, files) == 0)
		return (1);
	if (!ft_strcmp(files,".") || !ft_strcmp(files, ".."))
		return (0);
	cmp = file_list_comparison(search, files);
	return (cmp);
}


