/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:00:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 15:57:23 by hoomen           ###   ########.fr       */
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

# define ENDOFKEY "\'\" $"

/* expander.c */
char		**expander(char **argv, t_env *env, bool tilde_exp, bool quote_removal);
int			ft_argc(char **argv);

/* dollarsign.c */
void		expand_dollarsign(t_env *env, char *ptr, t_char_buf *buf);

/* buf_utils.c */
void		init_char_buf(t_char *buf);
void		resize_buffer(t_char *buf);

/* exp_utils.c */
int			change_quote_modus(int *quote_modus, char quote_found);



#endif
