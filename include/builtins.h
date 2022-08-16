/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:20:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 11:33:22 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

/* builtin echo */
void	mini_echo(int argc, char **argv);

/* builtin cd */
void	mini_cd(int argc, char **argv, t_env *env);

/* builtin env */
void	mini_env(t_env *env);

/* builtin mini_unset */
void	mini_unset(char **argv, t_env *env);

/* sort_env2.c */
int		sort_env2(t_env *env);

/* merge2.c */
int		ms_merge(t_env_hash **table_ptrs, int l, int m, int r);

#endif
