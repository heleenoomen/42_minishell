/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:35:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 18:14:32 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdlib.h>
# include<unistd.h>
# include<stdio.h>
# include<signal.h>
# include<sys/wait.h>
# include<fcntl.h>
# include<limits.h>
# include<stdbool.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<errno.h>
# include"environment.h"
# include"ms_signals.h"
# include"ms_termios.h"
# include"expander.h"
# include"builtins.h"
# include"cmds.h"
# include"ms_exit.h"
# include"ft_printf.h"
# include"libft.h"
# include"environment.h"

/*global variable that keeps track of exit status*/
int	ms_exit;

/*panic.c*/
void	panic(char *message, t_env *env);
void	panic_file(char *file, t_env *env, short flags, bool *parent);
void	panic_cp(char *s, t_env *env, bool *parent);
char	*panic_cp_null(char *s, t_env *env, bool *parent);
char	*panic_file_null(char *file, t_env *env, short flags, bool *parent);

/*fork1.c*/
int	fork1(void);

/*find_path.c*/
char	*find_path(char *s, t_env *env, bool *path);

/*ms_utils.c*/
int		get_argc(char **argv);
int		free_ret(void *ptr, void *ptr2, int ret);

#endif
