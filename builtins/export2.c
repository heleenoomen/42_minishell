/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 11:15:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/19 16:42:31 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*returns false if quotes are within quotes of the other type
 * (single within double or double within single)
 * otherwise returns true
 * moves pointer beyond quotes
 */
bool	quotes_key(char c, int *quotes)
{
	if (c == '\'')
	{
		if (*quotes = DOUBLE_QUOTES)
			return (false);
		if (*quotes = SINGLE_QUOTES)
			*quotes = NO_QUOTES
		else
			*quotes = SINGLE_QUOTES;
	}
	else if (c == '\"')
	{
		if (*quotes = SINGLE_QUOTES)
			return (false);
		if (*quotes == DOUBLE_QUOTES)
			*quotes = NO_QUOTES;
		else
			*quotes = DOUBLE_QUOTES;
	}
	return (true);
}

/*checks if first character is alphabetical, underscore or quote, returns false if not
 * checks if key (the part of s until equal sign) has only alphanumeric characters, underscores
 * and quotes. If quotes are encounterd, calls quotes_key to check if quotes are permitted and change
 * quotes flag
 *  removes quotes from key
 *  replaces equal sign with null byte to null terminate key
 *  sets value pointer to first byte after equal sign */
bool	is_valid_key(char *s, char **value, int *quotes)
{
	char	*ptr;
	int		quotes;
	

	if (!ft_isalpha(ptr[0]) && ptr[0] != '_' && ptr[0] != '\"' && ptr[0] != '\'')
		return (false);
	ptr = *s;
	while(*ptr)
	{
		if (ft_isalnum(*ptr) || *ptr == '_')
		{
			*s = *ptr;
			ptr++;
			s++;
		}
		else if (*ptr == '\'' || *ptr == '\"')
		{
			if(!quotes_key(*ptr, quotes)
				return (false);
			ptr++;
		}
		else
			return (false);
	}
	*s = '\0';
	*value = ptr + 1;
	return (true);
}

	
bool	is_valid_name(char *value, int *quotes)
{
	while (*value)
	{
		if

bool	expand_key(char *s, char **key)
{
	*key = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (key == NULL)
	{
		printf("System error\n");
		return (false);
	}


/* calls make_key_and_value_export to place null terminators for key and value
 * calls is_valid_key and is_valid_name to check if name and key are valid*/
bool	is_valid(char **s, char **value);
{
	int		quotes	
	size_t	i;
	char	*key
	
	quotes = NO_QUOTES;
	if(!is_valid_key(s, value, &quotes)
		return (false);
	if(!is_valid_name(value))
		return (false);
	return (true);
}


void	export(int argc, char **argv, t_env *env)
{
	int			i;
	t_env_pair	*new;
	char		*key;
	char		*value;

	if (argc == 1)
		print_env(env);
	i = 0;
	while (argv[i] != NULL)
	{
		if(!is_valid(&(argv[i]), &value)
			perror(argv[i]);
		else
		{
			if (!expand_key(argv[i], &key)
				return ;
			expand_value(&value);
			add_to_env(key, value, env);
			i++;
	}	
}
