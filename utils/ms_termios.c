/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_termios.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 18:02:37 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 18:24:49 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* makes sure that the ctrl-keystroke does not get printed while minishell is
 * running.
 * makes a copy of the original terminal settings and stores it in terimos_cpy
 * to be able to reset when minishell exits.
 */
void	cancel_echoctl(struct termios *termios_cpy)
{
	struct termios settings;

	tcgetattr(1, termios_reset);
	tcgetattr(1, &settings);
	settings.c_lflag &= ~ECHOCTL;
	tcsetattr(1, TCSAFLUSH, &settings);
}

/* resets ctrl-keystroke setting
 */
void	reset_echoctl(struct termios *termios_cpy)
{
	tcsetattr(1, TCSAFLUSH, termios_reset);
}
