/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_buf_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:09:17 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 13:20:19 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*initialize the buffer struct. Allocates an initial 128 bytes in the char_buf,
 * enough for 127 characters plus terminating nul byte). Sets size to 0 and free
 * to 127*/
void	init_char_buf(t_char_buf *buffer)
{
	buffer->char_buf = ft_calloc(128, sizeof(char));
	if (buffer == NULL)
		return ;
	buffer->size = 0;
	buffer->free = 127;
}

/* reallocs the char buffer to a buffer 128 bytes bigger
 * copies existing bytes and fills the rest of the buffer with
 * nul bytes. Sets free field to 128 and frees old buffer
 */
void	resize_buffer(t_char_buf *buffer)
{
	char	*new;
	int		i;
	int		j;
	
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


