/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:28:45 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/12 13:22:30 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void	parsing_syntax_error(char *token)
{
	char	*error_message;
	char	*temp;

	g_global_exit_status = 2;
	if (token)
	{
		temp = ft_strjoin("syntax error near unexpected token `", token);
		error_message = ft_strjoin(temp, "´");
		free(temp);
		error_shell(error_message, ERROR_UNDEFINED);
		free (error_message);
	}
	else
	{
		error_message = "parse error near`\\n´";
		error_shell(error_message, ERROR_UNDEFINED);
	}
}

int		parsing_lexer_error(void)
{
	g_global_exit_status = 2;
	error_shell("parse error: unbalanced quotes", ERROR_UNDEFINED);
	return (EXIT_ERROR_DEFAULT);
}

void	exec_command_error(char *cmd, int flag)
{
	char	*error_message;

	if (flag == 1)
		error_message = ft_strjoin(cmd, ": is a directory");
	else
		error_message = ft_strjoin(cmd, ": command not found");
	error_shell(error_message, ERROR_UNDEFINED);
	free(error_message);
	g_global_exit_status = (127 - flag);
}

int	error_shell(char *error_message, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	if (flag == ERROR_UNDEFINED)
		ft_putendl_fd(error_message, 2);
	else if (flag == ERROR_PERROR)
		perror(error_message);
}