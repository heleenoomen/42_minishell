/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:14:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/20 13:07:41 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"
#include "expand.h"

void	init_char_buf(t_char_buf *charbuf)
{
	charbuf->char_buf = ft_calloc(128, sizeof(char));
	if (buffer == NULL)
		return ;
	charbuf->size = 0;
	charbuf->free = 128;
}

void	resize_buffer(t_char_buf *charbuf)
{
	char	*new;
	int		i;
	
	new = ft_calloc(charbuf->size + 128, sizeof(char));
	if (new != NULL)
	{
		while (i < charbuf->size)
		{
			new[i] = charbuf->char_buf[i];
			i++:
		}	
		charbuf->free = 128;
	}
	free(charbuf->char_buf);
	charbuf->char_buf = new;
}

void	add_to_buf(t_char_buf *buffer, char c)
{
	if (buffer->free == 0)
	{
		resize_buuffer(charbuf);
		if (buffer->char_buf == NULL)
			return ;
	}
	key->char_buf[key->size] = c;
	key->size++;
	key->free--;
}

void	quotes(t_char_buf *buffer, char c, int *quotes)
{
	if (c == '\'')
	{
		if (*quotes == NO_QUOTES)
			*quotes == SINGLE_QUOTES;
		else if (*quotes == DOUBLE_QUOTES)
			add_to_buf(buffer, c);
		else
			*quotes == NO_QUOTES;
	}
	else if (c == '\"')
	{
		if (*quotes == NO_QUOTES)
			*quotes == DOUBLE_QUOTES;
		else if (*quotes == SINGLE_QUOTES)
			add_to_buf(buffer, c);
		else
			*quotes == NO_QUOTES;
	}
}

void	get_variable(char **local, t_char_buf *buffer, int *quotes, t_env *env)
{
	size_t	len;
	char 	*var;
	char	*key;
	int		i;
	int		j;
	
	var = *local;
	len = 0;
	while (var[len])
	{
		if (*end_of_var == ' ')
			break ;
		if (*end_of_var == '\'')
			break ;
		if (*end_of_var == '\"')
			break ;
		len++;
	}
	i = 0;
	while (i < env->size)
	{
		key = env->arr_pairs[i]->key;
		if (ft_strncmp(key, var, len) == NULL)
		{
			j = 0;
			while (env->arr_pair
}
	

void	dollarsign(t_char_buf *buffer, char **ptr, int *quotes, t_env *env)
{
	char	*variable;
	char	*local;

	local = *ptr;

	if (*quotes == SINGLE_QUOTES)
		add_to_buf(buffer, *ptr);
	else if (local[1] == '\'' && *quotes == NO_QUOTESS)
	{
		local++;
		*quotes = SINGLE_QUOTES
	}
	else if (local[1] == '\'' && *quotes == DOUBLE_QUOTES)
		add_to_buf(buffer, *local);
	else if (local[1] == '\"' && *quotes == DOUBLE_QUOTES)
		add_to_buf(buffer, *local);
	else if (local[1] == '\"' && *quotes == NO_QUOTES)
	{
		local++;
		get_variable(&local, buffer, quotes, env);
	}
}

char	*expand(char *s, int *quotes, t_env *env)
{
	t_char_buff	char_buffer;
	char		*ret;
	char		*ptr;

	init_char_buffer(&char_buffer);
	if (char_buffer->char_buf == NULL)
		return (NULL);
	ptr = s;
	*quotes = NO_QUOTES;
	while (*ptr)
	{
		if (!ft_strchr(TOKS_EXPAND, *ptr);
			add_to_buf(&char_buffer, *ptr);
		else if (ft_strchr(QUOTES, *ptr);
			quotes(&char_buffer, *ptr, quotes);
		else if (s[i] == '$')
			dollarsign(&char_buffer, *ptr, *quotes, env);
		if (char_buffer->char_buf == NULL)
			return (NULL);
		i++;
	}
	ret = ft_strdup(char_buffer->char_buf);
	free(char_buffer->char_buf);
	return (ret);
}

char	**expander(char **argv, t_env *env)
{
	char **argv_dup;
	int	quotes;
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	argv_dup = ft_calloc((i + 1), sizeof(char *));
	if (argv_dup == NULL)
		return (NULL);
	i = 0;
	while (argv[i] != NULL)
	{
		argv_dup[i] = expand(argv[i], &quotes);
		if (argv_dup[i] == NULL)
		{
			free_argv_dup(&argv_dup);
			return (NULL):
		}
		i++;
	}
	return (argv_dup);
}
