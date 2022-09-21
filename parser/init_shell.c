/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:40:14 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/21 13:47:13 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	launch_table(void (***table)(t_list **, enum e_grammar))
{
	int	i;
	int	j;

	i = 0;
	while (i < NONTERM)
	{
		j = 0;
		while (j < TOKENS)
		{
			table[i][j] = NULL;
			j++;
		}
		i++;
	}
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
	shell->env = malloc(sizeof(t_env)); // add protection here //
	init_env(shell->env, envp, shell);
	shell->table = malloc(NONTERM * sizeof(void***)); // add protection here //
	while (col < NONTERM)
	{
		shell->table[col] = malloc(TOKENS * sizeof(void**)); // add protection here //
		col++;
	}
	launch_table(shell->table);
}

