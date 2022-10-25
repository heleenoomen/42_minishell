/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:46:10 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/25 16:49:48 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	mini_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (error_builtins("pwd", NULL, EXIT_ERROR_DEFAULT));
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	free(pwd);
}
