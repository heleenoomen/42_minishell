/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:26:01 by kanykei           #+#    #+#             */
/*   Updated: 2022/08/17 16:43:20 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "lists/list.h"
# include "../ast.h"

g_global_exit_status 
typedef struct s_exec
{
	char		**curr_cmd;
	int			status;
	int			pipe_fd[2];
	int			pid;
	int			fd_in;
	int			fd_out;
	int			builtin;
	int			pipe;
	int			forks;
	t_list		**cmds_list;
	t_cmd_def	*cmd_type;
}	t_exec;


#endif
