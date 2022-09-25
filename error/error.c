/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 12:28:45 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/25 18:22:22 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	redirect_error(char *error_message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putendl_fd(": failed to redirect", 2);
	g_global_exit_status = 1;
	return (1); // ? this function had no return line, I changed it to make it compile (ho) //
}

int	expansion_error(char *error_message, int flag)
{
	if (flag == ERROR_REDIR)
		redirect_error(error_message);
	if (flag == ERROR_CMD)
		simple_command_error(error_message);
	return (1);
}

void	simple_command_error(char *error_message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error_message, 2);
	ft_putendl_fd(": argument is too long", 2);
	g_global_exit_status = EXIT_CANNOT_EXECUTE;
}

int	error_shell(char *error_message, int flag)
{
	ft_putstr_fd("minishell: ", 2);
	if (flag == ERROR_UNDEFINED)
		ft_putendl_fd(error_message, 2);
	else if (flag == ERROR_PERROR)
		perror(error_message);
	g_global_exit_status = EXIT_FAILURE;
	return (1);
}

void	error_set_global_exit_status(int flag)
{
	if (flag == ENOENT)
		g_global_exit_status = EXIT_CMD_NOT_FOUND;
	else if (flag == EACCESS)
		g_global_exit_status = EXIT_CANNOT_EXECUTE;
	else if (flag == ENOMEM)
		g_global_exit_status = EXIT_OUT_OF_MEMORY;
	else
		g_global_exit_status = EXIT_ERROR_DEFAULT;
}
void	error_builtins(char *builtin, char *argument, int flag)
{
	if (flag == ERROR_PERROR && argument != NULL)
		print_error(builtin, NULL, argument, 0);
	else if (flag == ERROR_PERROR)
		print_error(NULL, NULL, builtin, 0);
	else
		print_error(builtin, argument, NULL, flag);
	if (flag == ENOMEM)
		g_global_exit_status = EXIT_OUT_OF_MEMORY;
	else
		g_global_exit_status = EXIT_ERROR_DEFAULT;
}

int	error_builtins_int(char *builtin, char *argument, int flag)
{
	error_builtins(builtin, argument, flag);
	return (-1);
}

char	*path_error(char *s, int flag)
{
	if (flag == ENOENT)
		flag = EXIT_CMD_NOT_FOUND;
	print_error(s, NULL, NULL, flag);
	error_set_global_exit_status(flag);
	return (NULL);
}

bool	error_builtins_bool(char *builtin, char *argument, int flag, bool ret)
{
	error_builtins(builtin, argument, flag);
	return (ret);
}
