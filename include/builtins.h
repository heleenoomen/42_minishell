/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 16:20:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/13 16:05:16 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "ms_typedefs.h"

/* builins.c */
int		builtin(t_list *cmd, t_minishell *minishell);

/* builtin echo */
void	mini_echo(t_list *cmd);

/* builtin cd */
void	mini_cd(t_list *cmd, t_env *env);

/* builtin env */
void	mini_env(t_env *env);

/* builtin mini_unset */
void	mini_unset(t_list *cmd, t_env *env);

/* builtin mini_pwd */
void	mini_pwd(void);

/* builtin mini_export */
bool	first_char_valid(char c);
void	mini_export(t_list *cmd, t_env *env);

/* builtin mini_exit */
void	mini_exit(t_minishell *minishell);

# define WARNING_OLDPWD "minishell: unable to update OLDPWD variable\
(System error)"
# define WARNING_PWD "minishell: unable to update PWD variable\
(System error)"

#endif
