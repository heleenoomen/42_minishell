/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:20:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/11 14:12:17 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* builtin echo */
void	mini_echo(int argc, char **argv);

/* builtin cd */
void	mini_cd(int argc, char **argv, t_env *env);

#endif
