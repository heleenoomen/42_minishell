/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanykei <kanykei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 18:40:14 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/13 11:56:42 by kanykei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	init_minishell(t_minishell *shell, char **envp)
{
	int	col;

	col = 0;
	shell->line_len = 0;
	shell->value = NULL;
	shell->env = ft_malloc(sizeof(env), INIT, EXIT, shell);
	init_env(shell->env, envp, shell);
	shell->table = ft_malloc(NONTERM * sizeof(void***), INIT, EXIT, shell); /* added protection */
	while (col < NONTERM)
	{
		shell->table[col] = ft_malloc(TOKENS * sizeof(void**), INIT, EXIT, shell); /* added protection */
		col++;
	}
	launch_table(shell->table);
}

