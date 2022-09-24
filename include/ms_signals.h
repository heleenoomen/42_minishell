/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:37:31 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/24 13:03:40 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

// void	signals_interactive_mode(struct termios *termios_cpy);
void	signals_interactive_mode(void);
void	signals_parent_process(void);
// void	signals_child_process(struct termios *termios_cpy);
void	signals_child_process(void);

#endif