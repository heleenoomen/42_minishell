/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:40:14 by ktashbae          #+#    #+#             */
/*   Updated: 2022/10/25 16:48:36 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	launch_table(void (***table)(t_list **, enum e_grammar))
{
	start_and_or(table);
	pipe_and_subshell(table);
	commandset_and_io_here_file(table);
	child_commands(table);
	split_to_prefix(table);
	get_suffix_cmd(table);
	run_redirections_grand(table);
}

void	init_minishell(t_minishell *shell, char **envp)
{
	int	col;

	col = 0;
	shell->line_len = 0;
	shell->line = NULL;
	shell->env = ft_calloc(1, sizeof(t_env));
	if (shell->env == NULL)
		exit_minishell(ENOMEM, INIT, NULL, shell);
	init_env(shell->env, envp, shell);
	shell->table = ft_calloc(NONTERM, sizeof(void **));
	if (shell->table == NULL)
		exit_minishell(ENOMEM, INIT, NULL, shell);
	while (col < NONTERM)
	{
		shell->table[col] = ft_calloc(TOKENS, sizeof(void *));
		if (shell->table[col] == NULL)
			exit_minishell(ENOMEM, INIT, NULL, shell);
		col++;
	}
	launch_table(shell->table);
}
