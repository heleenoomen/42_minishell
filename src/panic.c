/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:57:59 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 13:19:32 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic(char *message, t_env *env)
{
	perror(message);
	if (env != NULL)
		clear_env(env);
	exit(errno);
}

void	panic_file(char *file, bool file_exists, t_env *env, int type)
{
	if (file_exists)
	{
		ft_printf("%s: permisson denied\n", file);
		clear_env(env);
		exit(128);
	}
	if (type == PA)
	{
		ft_printf("%s: no such file or directory\n", file);
		clear_env(env);
		exit(127);
	}
	if (type == EX)
	{
		ft_printf("%s: command not found\n", file);
		clear_env(env);
		exit(126);
	}
}

void panic_file_parent(char *file, bool file_exists, int type)
{
	if (file_exists)
	{
		ft_printf("%s: permisson denied\n", file);
		ms_exit = 128;
	}
	else if (type == PA)
	{
		ft_printf("%s: no such file or directory\n", file);
		ms_exit = 127;
	}
	else if (type == EX)
	{
		ft_printf("%s: command not found\n", file);
		ms_exit = 126;
	}
}

void	panic_cp(char *s, t_env *env, bool *parent)
{
	perror(s);
	ms_exit = errno;
	if (*parent == true)
		return ;
	if (env != NULL)
		clear_env(env);
	exit(ms_exit);
}
