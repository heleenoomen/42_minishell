/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_termios.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:13:31 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 18:23:00 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TERMIOS_H
# define MS_TERMIOS_H

void	cancel_echoctl(struct termios *termios_reset);
void	reset_echoctl(struct termios *termios_reset);

#endif
