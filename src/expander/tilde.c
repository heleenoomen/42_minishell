/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 17:24:22 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/19 18:04:30 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tilde_to_new_buf(char *tilde, t_char_buf *buf, int tilde_len)
{
	char	*new_buf;
	int		i;

	new_buf = malloc((((buf->size / 128) * 128) + 256) * sizeof(char));
	if (new_buf == NULL)
	{
		free(buf->buf);
		buf->buf = NULL;
		return ;
	}
	i = 0;
	ft_memmove(new_buf, tilde, tilde_len);
	ft_memmove(new_buf + tilde_len, buf->buf + 1, buf->size);
	buf->size += tilde_len - 1;
	buf->free += sizeof(new_buf) - buf->size;
	ft_memset(new_buf + buf->size, 0, buf->free + 1);
	free(buf->buf);
	buf->buf = new_buf;
	buf->size += tilde_len - 1;
	buf->free += 128;
}
			
void	expand_tilde(t_env *env, char *ptr, t_char_buf *buf)
{
	char	*tilde;
	int		len;

	if (*ptr != '~')
		return ;
	if (*(ptr + 1) != '/' && (*(ptr +1)) != '\0')
		return ;
	tilde = find_value(env, "HOME");
	if (tilde == NULL)
		return ;
	len = ft_strlen(tilde);
	if ((int) ft_strlen(tilde) + buf->size > buf->free)
		return (tilde_to_new_buf(tilde, buf, len));
	ft_memmove(buf->buf + len, buf->buf + 1, buf->size - 1);
	ft_memmove(buf->buf, tilde, len);
	buf->size += len - 1;
	buf->free -= len + 1;
}
