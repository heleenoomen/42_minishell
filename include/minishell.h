/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:35:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/10 16:23:37 by hoomen           ###   ########.fr       */
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
# include"expander.h"
# include"builtins.h"
# include"cmds.h"
# include"libft.h"

/*panic.c*/
void	panic_builtins(char *message, t_env *env);

/*fork1_panic.c*/
int	fork1(void);
void	panic(char *s);

/*find_path.c*/
char	*make_path(char *s, t_env *env);

#endif
