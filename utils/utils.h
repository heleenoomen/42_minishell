/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:11:47 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/07 11:30:54 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H

/* error.c */
void	*error_ptr(*int status, int error_code);
void	error_void(*int status, int error_code);

/* ms_termios.c */
void	cancel_echoctl(struct termios *termios_cpy);
void	reset_echoctl(struct termios *termios_cpy);

void	*ft_malloc(size_t size, int *status);
void	*ft_calloc2(size_t size, int *status);

/* ms_utils.c */ //*check if I use it in the end or not... *//
int		free_ret(void *ptr, void *ptr2, int ret);

/* ms_signals.c */
void	signal_interactive_mode(void);

#endif
