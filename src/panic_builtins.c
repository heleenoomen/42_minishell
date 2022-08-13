/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:57:59 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/12 17:53:58 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic(char *message, t_env *env)
{
	perror(message);
	if (env != NULL)
		clear_env_data(env);
	exit(errno);
}

void	panic_file(char *file, bool file_exists, t_env *env, int type)
{
	if (file_exists)
	{
		ft_printf("%s: permisson denied", file);
		clear_env_data(env);
		exit(128);
	}
	if (type == PA)
	{
		ft_printf("%s: no such file or directory", file);
		clear_env_data(env);
		exit(127);
	}
	if (type == EX)
	{
		ft_printf("%s: command not found", file);
		clear_env_data(env);
		exit(126);
	}
}

