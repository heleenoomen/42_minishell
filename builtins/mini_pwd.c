/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:46:10 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/22 17:05:07 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		g_global_exit_status = EXIT_ERROR_DEFAULT;
		return (error_builtins("pwd", ERROR_PERROR));
	}
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
}

