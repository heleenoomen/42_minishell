/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:42:46 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/19 18:13:00 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtins.h"

char	*construct_char_buffer(void)
{
	char	*buffer;

	buffer = ft_calloc(126, sizeof(char));
	if (buffer == NULL)
		printf("System error");
	return (buffer);
}

void	init_char_buf(t_char_buf *charbuf)
{
	charbuf->char_buf = ft_calloc(126, sizeof(char));
	if (buffer == NULL)
		printf("System error");
	charbuf->size = 0;
	charbuf->free = 126;
}

int	resize_buffer(t_char_buf *charbuf)
{
	char	*new;
	int		i;
	
	new = ft_calloc(charbuf->size + 126, sizeof(char));
	if (new == NULL)
	{
		printf("System error");
		return (1);
	}
	i = 0;
	while (i < charbuf->size)
	{
		new[i] = charbuf->char_buf[i];
		i++:
	}
	charbuf->size += 126;
	charbuf->free = 126;
	free(charbuf->char_buf);

	charbuf->char_buf = new;
	return (0);
}

int	add_to_buf(t_char_buf *key, char c)
{
	if (key->free == 0)
	{
		if (resize_buffer(key))
			return (MEM_ERROR);
	}
	key->char_buf[key->size] = c;
	key->size++;
	key->free--;
	return (0);
}

int	expand_key(char *s, t_char_buf *key, t_env *env)
{
	
	return (0);
}

int	make_key(char *s, t_char_buf *key, int *quotes, t_env *env)
{
	int	ret;

	ret = 0;
	if (ft_isalpha(*s) && !ft_strchr(FIRST_CHAR_KEY, *s))
		return (INVALID_INPUT);
	while (*s != '=')
	{
		if (*s == '\'' || *s == '\"')
		{
			if (!quotes_key(*s, quotes)
				return (INVALID_INPUT);
		}
		else if (ft_isalnum(*s) || *s == '_')
			ret = add_to_buff(key, *s);				
		else if (*s = '$')
			ret = expand_key(s, key, env);
		if (ret)
			return (ret);
		s++;
	}
	return (0);
}

int	make_key_and_value_export(char *s, t_char_buf *key, t_char_buf *value, t_env *env)
{
	int		quotes;
	int		ret;
	
	quotes = NO_QUOTES;
	ret = make_key(s, key, env);
	if (ret)
	{
		free(key.char_buf);
		free(value.char_buf);
		return (ret);
	}
	ret = make_value(s, value, env)
	if (ret)
	{
		free(key.char_buf);
		free(value.char_buf);
		return (ret);
	}
	return (0);
}

void	export(int argc, char **argv, t_env *env)
{
	int			i;
	t_char_buf	key;
	t_char_buf	value;

	if (argc == NULL)
	{
		print_export(env);
		return ;
	}
	i = 0;
	init_char_buf(&key);
	init_char_buf(&value);
	if (key.char_buf == NULL || value.char_buf == NULL)
	{
		printf("System error\n");
		return ;
	}
	while (argv[i] != NULL)
	{
		if (make_key_and_value_export(argv[i]), &key, &value, env);
			perror(argv[i]);
		else
			export_to_env(key->char_buf, value->char_buf);
		i++;
	}
}

