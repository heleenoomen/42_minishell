/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:35:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/20 18:02:56 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
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
# include"cmds.h"
# include"libft.h"
# include"get_next_line.h"



/*panic.c*/
void	panic_builtins(char *message, t_env *env);

/*fork1_panic.c*/
int	fork1(void);
void	panic(char *s);

#endif
