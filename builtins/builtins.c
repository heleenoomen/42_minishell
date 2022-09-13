/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:53:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/13 16:07:31 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_builtins(char *builtin_name, char *error)
{
	ft_putstr_fd(builtin_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
}

/* checks if a cmd is a builtin. If so, calls the builtin function to
 * execute the builtin command and returns true. If the command is not
 * a builtin, returns false
 */
int	builtin(t_list *cmd, t_minishell *minishell)
{
	char	*s;

	s = cmd->content;
	if (ft_strncmp_uplo(s, "echo", 5) == 0)
		mini_echo(cmd);
	else if (ft_strcmp(s, "cd") == 0)
		mini_cd(cmd, minishell->env);
	else if (ft_strcmp(s, "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(s, "export") == 0)
		mini_export(cmd, minishell->env);
	else if (ft_strcmp(s, "unset") == 0)
		mini_unset(cmd, minishell->env);
	else if (ft_strcmp(s, "env") == 0)
		mini_env(minishell->env);
	else if (ft_strcmp(s, "exit") == 0)
		mini_exit(minishell);
	else
		return (false);
	return (true);
}
				
