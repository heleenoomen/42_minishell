/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:11:47 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/25 13:49:46 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H

# include <termios.h>

/* error.c */
void	*error_ptr(int *status, int error_code);
void	error_void(int *status, int error_code);

/* ms_utils.c */ //*check if I use it in the end or not... *//
int		free_ret(void *ptr, void *ptr2, int ret);

# define INIT_ENV 0

# define NO_EXIT 0
# define DO_EXIT 1

#endif

