/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:20:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/19 13:52:28 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* builins.c */
int		builtin(char **argv, t_env *env);

/* builtin echo */
void	mini_echo(int argc, char **argv);

/* builtin cd */
void	mini_cd(int argc, char **argv, t_env *env);

/* builtin env */
void	mini_env(t_env *env);

/* builtin mini_unset */
void	mini_unset(int argc, char **argv, t_env *env);

/* builtin mini_pwd */
void	mini_pwd(void);

/* builtin mini_export */
bool	first_char_valid(char c);
void	mini_export(int argc, char **argv, t_env *env);

/* builtin mini_exit */
void	mini_exit(t_env *env);

#endif
