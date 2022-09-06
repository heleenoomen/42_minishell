/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:00:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/06 15:11:33 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_mini_us(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (i == (size_t) -1)
			return (false);
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	mini_unset(t_list *cmd, t_env *env)
{
	int		i;
	int		argc;
	char	**argv;

	argv = list_to_argv(cmd);
	if (argv == NULL)
		return ;
	if (argc == 0)
		return ;
	i = 0;
	while (argv[i] != NULL)
	{
		if (is_valid_mini_us(argv[i]))
			del_tree_node(&(env->tree), NULL, argv[i], 0);
		else
		{
			ft_putstr_fd("unset: ", 1);
			ft_putstr_fd(argv[i], 1);
			ft_putstr_fd(": invalid identifier\n", 1);
		}
		i++;
	}
	free(argv);
}

