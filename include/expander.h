/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:00:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/16 19:12:52 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "ms_typedefs.h"

typedef struct s_char_buf
{
	char	*buf;
	int		size;
	int		free;
}			t_char_buf;

# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

# define BUFSIZE 128

/* expander.c */
int			expander(t_list *nodes, t_env *env);

/* dollarsign.c */
void		expand_dollarsign(t_env *env, char *ptr, t_char_buf *buf);

/* quote_removal.c */
void		exp_remove_quotes(t_char_buf *buf);

/* tilde.c */
void		expand_tilde(t_env *env, t_char_buf *buf);

/* buf_utils.c */
void		init_char_buf(t_char_buf *buf);
void		resize_buffer(t_char_buf *buf);
void		add_char_to_buf(t_char_buf *buf, char c);
void		add_str_to_buf(t_char_buf *buf, char *s);

/* exp_utils.c */
int			change_quote_modus(int *quote_modus, char quote_found);

#endif
