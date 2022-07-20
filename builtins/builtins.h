/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:00:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/20 13:52:35 by hoomen           ###   ########.fr       */
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
# define DOUBLE_QUOTE 2

# define ENDOFVAR "\'\"\$ "
# define MEM_ERROR 1
# define INVALID_INPUT 2

/*init_char_buff
 * allocates 128 chars in buffer
 * sets size to 0
 * sets free to 128
 * error checking in calling function: if buffer.char_buf == NULL
 */
void		init_char_buf(t_char_buf *charbuf);

/* resizes the buffer in case free = 0.
 * resets 
#endif
