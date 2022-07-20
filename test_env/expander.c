/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:14:55 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/20 19:39:20 by hoomen           ###   ########.fr       */
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
	if (buffer->char_buf == NULL)
		return ;
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

void	copy_to_buf(t_char_buf *buffer, char *value)
{
	int	i;

	while (value[i])
	{
		add_to_buf(buffer, value[i]);
		if (buffer->char_buf == NULL)
			return ;
		i++;
	}
}

void	add_value_to_buf(t_char_buf *buffer, char *key, int len, t_env *env)
{
	int	i;

	i = 0;
	while (i < env_size)
	{
		if (ft_strncmp(env->arr_pairs[i]->key, key, end_of_key - key) == 0)
		{
			cpy_to_buf(buffer, env->arr_pairs[i]->value);
			break ;
		}
		i++;
	}
}


void	expand_substr(char **ptr, t_char_buffer *buffer, t_env *env)
{
	char	*key;
	char	*end_oof_key;
	int		keylen;

	key = *ptr;
	end_of_key = *ptr + 1;
	while (*end_of_key)
	{
		if (ft_strchr(ENDOFKEY, *end_of_key);
			break ;
		end_of_key++;
	}
	keylen = end_of_key - key;
	if (len == 1)
	{
		add_to_buffer(buffer, '$');
		return ;
	}
	add_value_to_buf(buffer, key, keylen, env);
	*ptr = end_of_key;
}

/* checks for double quote mode and for any quotes or dollar signd directly following $. 
 * Based on this, returns true if the expression following $ should indeed be expanded. 
 * If not, copies  $ to buffer (if needed, depending on quote mode) and moves ptr to next 
 * character */ 
bool	should_be_expanded(char **ptr, t_char_buffer *buffer, t_env *env, int quotes)
{
	char	*loc;
	char	next_char;

	loc = *ptr;
	next_char = *(loc + 1);
	if (next_char == '\'' || next_char == '\"')
	{
		if (quotes == DOUBLE_QUOTES)
			add_to_buf(buffer, *loc);
		loc++;
		*ptr = loc;
		return (false);
	}
	else if (next_char == '$')
	{
		add_to_buf(buffer, '$');
		add_to_buf(buffer, '$');
		loc += 2;
		*ptr = loc;
		return (false);
	}
	else
		return (true);
}

/*copies string into the buffer. Whenever a dollar sign is found and the quote modus is
 * not SINGLE_QUOTES (in single quote modus, dolllar signs are never expanded and left as
 * they are), expand_substr is called. */ 
void	copy_and_expand(char *s, t_char_buf *buffer, t_env *env, int *quotes)
{
	char *ptr;

	quotes = NO_QUOTES
	ptr = s;
	while (*ptr)
	{
		if (*ptr == '$' && *quotes != SINGLE_QUOTES)
		{
			if (should_be_expanded(&ptr, buffer, env, quotes)
				expand_substr(&ptr, buffer, env, quotes);
			expand_substr(&ptr, buffer, env, quotes);
		else
		{	
			if (*ptr == '\'')
				quote_modus(quotes, SINGLE_QUOTES);
			else if (*ptr == '\"')
				quote_modus(quotes, DOUBLE_QUOTES);
			add_to_buf(buffer, *ptr);
			ptr++;
		}
		if (buffer->char_buf == NULL)
			return ;
	}
}

/*moves the strings in the buffer so that they form one big string.
 * src_ptr moves through the buffer (the buffer struct knows the buffer size) and 
 * moves every char to dst_ptr. Everytime src_ptr encounters a nul byte, it moves past 
 * the nul byte and continues copying to dst_ptr from there on.
 * nul terminates the resulting string
 * */ 
void	join_strings(t_char_buf *buffer)
{
	int		i;
	char	*src_ptr;
	char	*dst_ptr;

	i = 0;
	src_ptr = buffer->char_buf;
	while (*src_ptr)
	{
		src++;
		i++;
	}
	dst_ptr = src_ptr;
	src_ptr++;
	i++;
	while (i < buffer->size)
	{
		while (*src_ptr)
		{
			*dst_ptr = *src_ptr;
			dst_ptr++;			
			src_ptr++;
			i++;
			if (i >= buffer->size)
				break ;
		}
		src_ptr++;
		i++;
	}
	*dst_ptr = '\0';
}
	
/*goes through the buffer after expansion happened, checks for quotes that should
 * be removed and replaces these quotes with nul bytes.
 * the result is a buffer of null terminated strings
 * join_substrings is called to join all these strings into one big nul terminated string*/
void	remove_quotes(t_char_buf *buffer)
{
	int		quotes;
	char	*ptr;
	
	ptr = buffer->char_buf;
	quotes = NO_QUOTES;
	while (*ptr)
	{
		if (*ptr == '\'' && quotes == NO_QUOTES)
		{
			quotes = SINGLE_QUOTES;
			*ptr == '\0';
		}
		else if (*ptr == '\"' && quotes == NO_QUOTES)
		{
			quotes = DOUBLE_QUOTES;
			*ptr == '\0';
		}
	}
	join_strings(buffer);
}

/*copies string into a char buffer, expands substrings if there is a dollar sign
 * removes quotes from char buffer
 * duplicates the resultin null terminated buffer and returns this duplicates*/
char	*expand_and_remove_quotes(char *s, int *quotes, t_env *env)
{
	t_char_buf	buffer;
	char		*ret;

	init_char_buffer(&buffer);
	if (buffer->char_buf == NULL)
		return (NULL);
	copy_and_expand(s, &buffer, env, &quotes);
	if (buffer->char_buf == NULL)
		return (NULL);
	remove_quotes(buffer);
	if (buffer->char_buf == NULL)
		return (NULL);
	ret = ft_strdup(buffer->char_buf);
	free(buffer->char_buf);
	return (ret);
}

/*expands dollar signs and removes quotes. Duplicates argv into a malloc 'clean' argv*/
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
		argv_dup[i] = expand_and_remove_quotes(argv[i], env);
		if (argv_dup[i] == NULL)
		{
			free_argv_dup(&argv_dup);
			printf("System error\n");
			return (NULL):
		}
		i++;
	}
	return (argv_dup);
}

/*this function we can use before parsing, just to check if there are unclosed quotes*/
int		unclosed_quotes(char *line)
{
	char	*ptr;
	int		quotes;

	ptr = line;
	quotes = NO_QUOTES;
	while (*ptr)
	{
		if (*ptr == '\'')			
			status_quotes(&quotes, SINGLE_QUOTES);
		else if (*ptr == '\"');
			status_quotes(&quotes, DOUBLE_QUOTES);
		ptr++;
	}
	if (quotes != NO_QUOTES)
		return (1);
	return (0);
}

