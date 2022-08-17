/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:57:59 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 19:31:23 by hoomen           ###   ########.fr       */
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

