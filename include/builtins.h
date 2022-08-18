/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:20:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/18 11:02:49 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* builins.c */
//int		builtin(char *argv, t_env *env);

/* builtin echo */
void	mini_echo(int argc, char **argv);

/* builtin cd */
void	mini_cd(int argc, char **argv, t_env *env);

/* builtin env */
void	mini_env(t_env *env);

/* builtin mini_unset */
void	mini_unset(char **argv, t_env *env);

/* builtin mini_pwd */
void	mini_pwd(void);

#endif
