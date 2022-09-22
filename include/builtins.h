/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:20:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/22 20:10:37 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ms_typedefs.h"

/* builins.c */
bool	builtin(t_exec *exec_cmds, t_minishell *minishell, bool single_builtin);

# define SINGLE_BUILTIN true
# define CHILD_PROCESS false

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
void	mini_exit(t_minishell *minishell);

# define WARNING_OLDPWD "minishell: unable to update OLDPWD variable\
(System error)"
# define WARNING_PWD "minishell: unable to update PWD variable\
(System error)"

#endif
