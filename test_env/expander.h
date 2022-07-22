/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:00:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/20 17:30:09 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_char_buf
{
	char	*char_buf;
	int		size;
	int		free;
}			t_char_buf;

# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

# define ENDOFVAR "\'\"$ "

/*init_char_buff
 * allocates 128 chars in buffer
 * sets size to 0
 * sets free to 128
 * error checking in calling function: if buffer.char_buf == NULL
 */
void		init_char_buf(t_char_buf *charbuf);

#endif
