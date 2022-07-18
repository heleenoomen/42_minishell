/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 15:35:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/18 13:44:02 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include<signal.h>
# include<readline/readline.h>
# include<readline/history.h>
# include"libft.h"

int	exitstatus;

typedef struct s_env_node
{
	char		*env_var;
	s_env_node	*next;
}				t_env_node;

/* t_env_data stores environment data
 * size = items in environment list
 * hash table keys:
 * 		A-Z = 0-25
 * 		_   = 26
 * 		a-z = 27-52 */
typedef struct s_env_data
{
	size_t		size;
	char		*envp;
	t_env_node	hash_table[53];
}				t_env_data;

/*main.c*/
void		sighandler(int sig);

/*parse.c*/
void		parse(char *buf);

/*panic.c*/
void		panic(char *message, t_env_data *env_data);

#endif
