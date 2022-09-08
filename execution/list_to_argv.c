/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_argv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 10:02:25 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/08 17:40:12 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* traverses the list that starts at cmd. Counts the nodes in order to
 * know argc. mallocs an array of char pointers the size argc + 1. 
 * lets every entry in argv point to the content of the nodes in the list.
 * NULL terminates the argv. returns the argv and sets argc (passed by 
 * reference)
 */
char	**list_to_argv(t_list *cmd, int *argc)
{
	t_list	*traverser;
	char	**argv;
	int		i;

	i = 0;
	traverser = cmd;
	while (traverser != NULL)
	{
		traverser = traverser->next;
		i++;
	}
	if (argc != NULL)
		*argc = i;
	argv = ft_malloc((i + 1) * sizeof(char *), cmd->content, NO_EXIT, NULL);
	if (argv == NULL)
		return (NULL);
	traverser = cmd;
	i = -1;
	while (traverser != NULL)
	{
		argv[++i] = traverser->content;
		traverser = traverser->next;
	}
	argv[i] = NULL;
	return (argv);
}

/* NB Currently the strings in the cmd list are NOT strdupped, i.e. when the t_list *cmd gets freed, we should NOT free the content because it will
 * leave garbage in the argv.
 */
