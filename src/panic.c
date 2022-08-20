/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:57:59 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/20 16:13:25 by hoomen           ###   ########.fr       */
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

void	panic_file(char *file, t_env *env, short flags, bool *parent)
{
	if (flags & EXIST)
	{
		ft_printf("%s: permisson denied\n", file);
		ms_exit = 128;
	}
	else if (flags & NOPA)
	{
		ft_printf("%s: no such file or directory\n", file);
		ms_exit = 127;
	}
	else if (flags & ISEXEC)
	{
		ft_printf("%s: command not found\n", file);
		ms_exit = 126;
	}
	if (*parent == true)
		return ;
	if (env != NULL)
		clear_env(env);
	exit(ms_exit);
}

char	*panic_file_null(char *file, t_env *env, short flags, bool *parent)
{
	panic_file(file, env, flags, parent);
	return (NULL);
}

char	*panic_cp_null(char *s, t_env *env, bool *parent)
{
	panic_cp(s, env, parent);
	return (NULL);
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
