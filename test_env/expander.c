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
#include "expander.h"

/*free argv_dup in case malloc fails somewhere in the
 * process of expanding*/
void	free_argv_dup(char ***argv_dup)
{
	int	i;
	char	**argv_dup_ptr;

	i = 0;
	while (argv_dup_ptr[i])
	{
		free(argv_dup_ptr[i]);
		i++;
		argv_dup_ptr[i] = NULL;
	}
	free(argv_dup_ptr);
	*argv_dup = NULL;
}

/*initialize the buffer struct. Allocates an initial 128 bytes
 * in the char_buf (enough for 128 characters). Sets size to 0 
 * and free to 128*/
void	init_char_buf(t_char_buf *buffer)
{
	buffer->char_buf = ft_calloc(128, sizeof(char));
	if (buffer == NULL)
		return ;
	buffer->size = 0;
	buffer->free = 128;
}

/*allocates a new char buffer that is 128 bytes bigger than the
 * existing buffer. copies the string in the existing buffer to 
 * the new buffer, fills the remaining space in the new buffer 
 * with nul bytes. sets the free field in the buffer struct to
 * 128. Frees the old character buffer and sets the char_buf 
 * pointer in the buffer struct to the newly created char buffer.
 */
void	resize_buffer(t_char_buf *buffer)
{
	char	*new;
	int	i;
	int	j;
	
	new = malloc((buffer->size + 128) * sizeof(char));
	if (new != NULL)
	{
		i = 0;
		while (i < buffer->size)
		{
			new[i] = buffer->char_buf[i];
			i++;
		}	
		j = 0;
		while (j < 128)
		{
			new[i + j] = '\0';
			j++;
		}
	}
	buffer->free = 128;
	free(buffer->char_buf);
	buffer->char_buf = new;
}

/*adds a character to the buffer and adjusts size and free accordingly.
 * If there is no free space left, resize_buffer is called to expand the
 * existing buffer*/
void	add_to_buf(t_char_buf *buffer, char c)
{
	if (buffer->char_buf == NULL)
		return ;
	if (buffer->free == 0)
	{
		resize_buffer(buffer);
		if (buffer->char_buf == NULL)
			return ;
	}
	buffer->char_buf[buffer->size] = c;
	buffer->size++;
	buffer->free--;
}

/*takes as a parameter a pointer to the quote mode (int quote_modus) and 
 * the type of quotes found (either SINGLE_QUOTES or DOUBLE_QUOTES).
 * If the quotes found are the same as the actual quote mode, it means that we
 * have found the end of the quotation, so quote_modus is set to NO_QUOTES.
 * If the actual modus is NO_QUOTES, it means that we have found the beginning
 * of a quotation and *quote is set to the type of quotations found.
 * single quotes are ignored when we are in double quote modus and vice versa
 * returns 1 if quote_modus is changed, otherwise returns 0*/
int	change_quote_modus(int *in_quotes, int quote_found)
{
	if (*in_quotes == NO_QUOTES)
	{
		*in_quotes = quote_found;
		return (1);
	}
	if (*in_quotes == quote_found)
	{
		*in_quotes = NO_QUOTES;
		return (1);
	}
	return (0);
}

/*copies string to buffer*/
void	add_value_to_buf(t_char_buf *buffer, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		add_to_buf(buffer, s[i]);
		if (buffer->char_buf == NULL)
			return ;
		i++;
	}
}

/*saves the char at end_of_key in temp and sets end_of_key to nul, so that key is a nul 
 * terminated string. Iterates through environment to search for matching key, using strcmp.
 * If found, returns a value to the corresponding value. If not found, returns NULL. Sets
 * the char at end_of_key back to its original char before returning*/
char	*find_key_value_pair(t_char_buf *buffer, char *key, char *end_of_key, t_env *env)
{
	int	i;
	char	temp;
	char	*value;

	i = 0;
	temp = *end_of_key;
	*end_of_key = '\0';
	while (i < env->size)
	{
		if (ft_strcmp(env->arr_pairs[i].key, key) == 0)
		{
			*end_of_key = temp;
			return (env->arr_pairs[i].value);
		}
		i++;
	}
	*end_of_key = temp;
	return (NULL);
}

/*sets pointer to beginning of key. Searches for end of key and sets end_of_key
 * pointer to first character after end of key. calls find_key_value_pair to check
 * if key exists and receives a pointer to value back (or NULL if key is not found)
 * calls add_value_to_buf to copy the value string to the buffer. Sets *ptr to
 * end_of_key*/
void	expand_substr(char **ptr, t_char_buf *buffer, t_env *env)
{
	char	*key;
	char	*end_of_key;
	char	*value;

	key = *ptr + 1;
	end_of_key = *ptr + 1;
	while (*end_of_key)
	{
		if (ft_strchr(ENDOFVAR, *end_of_key))
			break ;
		end_of_key++;
	}
	value = find_key_value_pair(buffer, key, end_of_key, env);
	if (value != NULL)
		add_value_to_buf(buffer, value);
	*ptr = end_of_key;
}

/* checks for double quote mode and for any quotes or dollar signd directly following $. 
 * Based on this, returns true if the expression following $ should indeed be expanded. 
 * If not, copies  $ to buffer (if needed, depending on quote mode) and moves ptr to next 
 * character */ 
bool	should_be_expanded(char **ptr, t_char_buf *buffer, t_env *env, int quotes_mode)
{
	char	*loc;
	char	next_char;

	loc = *ptr;
	next_char = *(loc + 1);
	if (next_char == '\'' || next_char == '\"')
	{
		if (quotes_mode == DOUBLE_QUOTES)
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
void	copy_and_expand(char *s, t_char_buf *buffer, t_env *env)
{
	char *ptr;
	int	in_quotes;

	in_quotes = NO_QUOTES;
	ptr = s;
	while (*ptr)
	{
		if (*ptr == '$' && in_quotes != SINGLE_QUOTES)
		{
			if (should_be_expanded(&ptr, buffer, env, in_quotes))
				expand_substr(&ptr, buffer, env);
		}
		else
		{	
			if (*ptr == '\'')
				change_quote_modus(&in_quotes, SINGLE_QUOTES);
			else if (*ptr == '\"')
				change_quote_modus(&in_quotes, DOUBLE_QUOTES);
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
		src_ptr++;
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
	int		in_quotes;
	char	*ptr;
	
	ptr = buffer->char_buf;
	in_quotes = NO_QUOTES;
	while (*ptr)
	{
		if (in_quotes == NO_QUOTES)
			printf("NO_QUOTES modus, *ptr = %c\n", *ptr);
		if (in_quotes == SINGLE_QUOTES)
			printf("SINGLE_QUOTES modus, *ptr = %c\n", *ptr);
		if (in_quotes == DOUBLE_QUOTES)
			printf("DOUBLE_QUOTES modus, *ptr = %c\n", *ptr);
		if (*ptr == '\'')
		{
			if (change_quote_modus(&in_quotes, SINGLE_QUOTES))
				*ptr = '\0';
		}
		else if (*ptr == '\"')
		{
			if (change_quote_modus(&in_quotes, DOUBLE_QUOTES))
				*ptr = '\0';
		}
		ptr++;
	}
	join_strings(buffer);
}

/* initializes char buffer struct
 * copies string into a char buffer, expands substrings if there is a dollar sign
 * removes quotes from char buffer
 * duplicates the resultin null terminated buffer and returns this duplicates*/
char	*expand_and_remove_quotes(char *s, t_env *env)
{
	t_char_buf	buffer;
	char		*ret;

	init_char_buf(&buffer);
	if (buffer.char_buf == NULL)
		return (NULL);
	copy_and_expand(s, &buffer, env);
	if (buffer.char_buf == NULL)
		return (NULL);
	remove_quotes(&buffer);
	if (buffer.char_buf == NULL)
		return (NULL);
	ret = ft_strdup(buffer.char_buf);
	free(buffer.char_buf);
	return (ret);
}

/*expands dollar signs and removes quotes. Duplicates argv into a malloc 'clean' argv*/
char	**expander(char **argv, t_env *env)
{
	char 		**argv_dup;
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
			return (NULL);
		}
		i++;
	}
	return (argv_dup);
}

/*this function we can use before parsing, just to check if there are unclosed quotes*/
int	unclosed_quotes(char *line)
{
	char	*ptr;
	int	in_quotes;

	ptr = line;
	in_quotes = NO_QUOTES;
	while (*ptr)
	{
		if (*ptr == '\'')			
			change_quote_modus(&in_quotes, SINGLE_QUOTES);
		else if (*ptr == '\"');
			change_quote_modus(&in_quotes, DOUBLE_QUOTES);
		ptr++;
	}
	if (in_quotes != NO_QUOTES)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	**argv_expanded;

	init_env(&env, envp);
	argv_expanded = expander(argv, &env);
	int i = 0;
	while (argv_expanded[i])
	{
		printf("%s\n", argv_expanded[i]);
		free(argv_expanded[i]);
		i++;
	}
	free(argv_expanded);
	clear_env_data;
}
