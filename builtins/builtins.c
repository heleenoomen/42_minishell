/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:53:06 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/22 16:07:00 by hoomen           ###   ########.fr       */
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
bool	builtin(t_list *cmd, t_minishell *minishell)
{
	char	*s;
	t_list	*args;

	args = ((t_ast *)(cmd->content))->cmds->cmd;
	s = args->content;
	dprintf(2, "builtin, s = %s\n", s);
	if (ft_strncmp_uplo(s, "echo", 5) == 0)
		mini_echo(args);
	else if (ft_strcmp(s, "cd") == 0)
		mini_cd(args, minishell->env);
	else if (ft_strcmp(s, "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(s, "export") == 0)
		mini_export(args, minishell->env);
	else if (ft_strcmp(s, "unset") == 0)
		mini_unset(args, minishell->env);
	else if (ft_strcmp(s, "env") == 0)
		mini_env(minishell->env);
	else if (ft_strcmp(s, "exit") == 0)
		mini_exit(minishell);
	else
		return (false);
	return (true);
}
				
