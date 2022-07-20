/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:14:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/20 13:54:46 by hoomen           ###   ########.fr       */
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

void	quote_modus(int *quotes, int quotechar)
{
	if (*quotes == NO_QUOTES)
		*quotes = quotechar;
	else if (*quotes == quotechar)
		*quotes = NO_QUOTES;
}

void	expand(char **ptr, t_char_buf *buffer, t_env *env, int *quotes)
{
	char	*var;
	char	*evar;
	char	temp;
	int		i;

	var = *ptr;
	evar = *ptr;
	while (*evar)
	{
		if (ft_strchr(ENDOFVAR, *evar);
			break ;
		evar++;
	}
	temp = *evar;
	*evar = '\0';
	i = 0;
	while (i < env_size)
	
}

void	scan_and_expand(char *s, t_char_buf *buffer, t_env *env, int *quotes)
{
	char	*ptr;

	ptr = s;
	*quotes = NO_QUOTES;
	while (*ptr)
	{
		if (*ptr == '$' && *quotes != SINGLE_QUOTES)
			expand(ptr, buffer, env, quotes);
		else
		{
			if (*ptr == '\'')
				quote_modus(quotes, SINGLE_QUOTES);
			else if (*ptr == '\"')
				quote_modus(quotes, DOUBLE_QUOTES);
			add_to_buf(buffer, *ptr);
			ptr++;
		}
	}
}

char	*make_def(char *s, int *quotes, t_env *env)
{
	t_char_buff	buffer;
	char		*ret;

	init_char_buffer(&buffer);
	if (buffer->char_buf == NULL)
		return (NULL);
	scan_and_expand(s, &buffer, env, &quotes);
	if (buffer->char_buf == NULL)
		return (NULL);
	remove_quotes(buffer);
	if (buffer->char_buf == NULL)
		return (NULL);
	ret = ft_strdup(buffer->char_buf);
	free(buffer->char_buf);
	return (ret);
}

char	**expander(char **argv, t_env *env)
{
	char 		**argv_dup;
	int			quotes
	int			i;
	
	i = 0;
	while (argv[i] != NULL)
		i++;
	argv_dup = ft_calloc((i + 1), sizeof(char *));
	if (argv_dup == NULL)
		return (NULL);
	i = 0;
	while (argv[i] != NULL)
	{
		argv_dup[i] = make_def(argv[i], env);
		if (argv_dup[i] == NULL)
		{
			free_argv_dup(&argv_dup);
			return (NULL):
		}
		i++;
	}
	return (argv_dup);
}
