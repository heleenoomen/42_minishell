/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:00:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 17:51:07 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_char_buf
{
	char	*buf;
	int		size;
	int		free;
}			t_char_buf;

# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

/* expander.c */
char		**expander(char **argv, t_env *env, bool tilde_exp, bool quote_removal);
int			ft_argc(char **argv);

/* dollarsign.c */
void		expand_dollarsign(t_env *env, char *ptr, t_char_buf *buf);

/* quote_removal.c */
void		remove_quotes(t_char_buf *buf);

/* tilde.c */
void		expand_tilde(t_env *env, char *ptr, t_char_buf *buf);

/* buf_utils.c */
void		init_char_buf(t_char_buf *buf);
void		resize_buffer(t_char_buf *buf);
void		add_char_to_buf(t_char_buf *buf, char c);
void		add_str_to_buf(t_char_buf *buf, char *s);

/* exp_utils.c */
int			change_quote_modus(int *quote_modus, char quote_found);

#endif
