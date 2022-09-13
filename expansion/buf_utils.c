/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:52:19 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/06 16:21:58 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*initialize the buffer struct. Allocates an initial BUFSIZE bytes in the char_buf,
 * enough for 127 characters plus terminating nul byte). Sets size to 0 and free
 * to 127*/
void	init_char_buf(t_char_buf *buf)
{
	buf->buf = ft_calloc2(BUFSIZE, NULL);
	if (buf->buf == NULL)
		return (NULL);
	buf->size = 0;
	buf->free = 127;
}

/* reallocs the char buffer to a buffer BUFSIZE bytes bigger
 * copies existing bytes and fills the rest of the buffer with
 * nul bytes. Sets free field to BUFSIZE and frees old buffer
 */
void	resize_buffer(t_char_buf *buf)
{
	char	*new;
	int		i;
	int		j;
	
	new = ft_malloc((buf->size + 1 + BUFSIZE) * sizeof(char), NULL);
	if (new != NULL)
	{
		i = 0;
		while (i < buf->size)
		{
			new[i] = buf->buf[i];
			i++;
		}	
		j = 0;
		while (j < BUFSIZE)
		{
			new[i + j] = '\0';
			j++;
		}
	}
	buf->free = BUFSIZE;
	free(buf->buf);
	buf->buf = new;
}

/* adds a character to the buffer and adjusts size and free accordingly.
 * resizes buffer if needed.
 */
void	add_char_to_buf(t_char_buf *buf, char c)
{
	if (buf->buf == NULL)
		return ;
	if (buf->free == 0)
	{
		resize_buffer(buf);
		if (buf->buf == NULL)
			return ;
	}
	buf->buf[buf->size] = c;
	buf->size++;
	buf->free--;
}

/*copies string to buffer*/
void	add_str_to_buf(t_char_buf *buf, char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
	{
		add_char_to_buf(buf, s[i]);
		if (buf->buf == NULL)
			return ;
		i++;
	}
}


