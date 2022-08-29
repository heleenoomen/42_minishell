/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:40:14 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/26 12:08:20 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../ast.h"

void	launch_table(void (***table)(t_list **, t_grammar))
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
	split_to_prefix(table);
	run_redirections_grand(table);
	commandset_and_io_here_file(table);
	get_suffix_cmd(table);
	child_commands(table);
}

void	init_minishell(t_minishell *shell)
{
	int	col;

	col = 0;
	shell->line_len = 0;
	shell->value = NULL;
	/*env */
	shell->table = malloc(NONTERM * sizeof(void***));
	while (col < NONTERM)
	{
		shell->table[col] = malloc(TOKENS * sizeof(void**));
		col++;
	}
	launch_table(shell->table);
}