/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:02:25 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/26 18:57:53 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_list *cmd)
{
	t_list	*trav;
	int		count;

	count = 0;
	trav = cmd;
	while (trav != NULL)
	{
		count++;
		trav = trav->next;
	}
	return (count);
}

/* traverses the list that starts at cmd. Counts the nodes in order to
 * know argc. mallocs an array of char pointers the size argc + 1. 
 * lets every entry in argv point to the content of the nodes in the list.
 * NULL terminates the argv. returns the argv and sets argc (passed by 
 * reference)
 */
char	**list_to_argv(t_list *cmd, int *argc)
{
	t_list	*trav;
	char	**argv;
	int		i;

	if (argc != NULL)
		*argc = count_args(cmd);
	argv = malloc((*argc + 1) * sizeof(char *));
	if (argv == NULL)
	{
		g_global_exit_status = ENOMEM;
		return (NULL);
	}
	trav = cmd;
	i = -1;
	while (trav != NULL)
	{
		argv[++i] = trav->content;
		trav->content = NULL;
		trav = trav->next;
	}
	argv[i + 1] = NULL;
	return (argv);
}

/* NB Currently the strings in the cmd list are NOT strdupped, i.e. when the
 * t_list *cmd gets freed, we should NOT free the content because it will
 * leave garbage in the argv.
 */
