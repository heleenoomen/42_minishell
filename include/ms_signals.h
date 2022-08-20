/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:00:49 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 18:13:05 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SIGNALS_H
# define MS_SIGNALS_H

void	ms_signal(t_env *env);
void	ms_sig_dfl(t_env *env);
void	ms_sigint_ignore(t_env *env);
void	ms_sigint(t_env *env);

#endif
