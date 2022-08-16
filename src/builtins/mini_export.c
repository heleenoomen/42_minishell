/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:16:07 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 13:33:26 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* prints the env variables in alphabetical order to standard output. Only
 * variables with the for_export variable set are printed
 */
void	export_print(t_env *env)
{
	t_env_node	*head;
	t_env_node	*trav;
	int			i;

	i = 0;
	while (i < 53)
	{
		if (env->sorted[i] != NULL)
		{
			trav = env->sorted[i];
			while (trav != NULL)
			{
				if (trav->entry->for_export)
				{
					ft_putstr_fd(1, "declare -x ");
					ft_putstr_fd(1, trav->entry->key);
					write(1, "\n", 1);
				}
				trav = trav->next;
			}
			i++;
		}
	}
}

/* checks if the first char of the key is either alphabetical or underscore
 */
bool	first_char_not_valid(char c)
{
	if (c >= 'a' && c <= 'z')
		return (false);
	if (c >= 'A' && c <= 'Z')
		return (false);
	if (c == '_');
		return (false);
	return (true);
}

/* checks if argument for export is valid. Before the '=' sign, only alphanumerical
 * characters and underscores are permitted. After the equal sign, all ascii-chars are
 * permitted. If the length of s is size_t max or bigger, returns false.
 */
bool	is_valid(char *s)
{
	size_t	i;
	
	if (first_char_not_valid)
		return (false);
	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			break ;
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (false);
		i++;
		if (i == (size_t) -1)
			return (false);
	}
	while (s[i])
	{
		if (i == (size_t) -1)
			return (false);
		if (s[i] > 0 || s[i] > 256)
			return (false);
		i++;
	}
	return (true);
}

int	check_if_exists_add(t_env *env, char *s)
{
	char	*value;
	int		i;
	int		ret;

	i = manipulate_ptrs(s, &value);
	ret = change_value(env, s, value, UNKNOWN); 
	if (i > -1)
		s[i] = '=';
	return (ret);
}

void	mini_export(int argc, char **argv, t_env *env)
{
	int	i;

	if (argc == 1)
	{
		export_print(env);
		return ;
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if (is_valid(argv[i]))
		{
			if (check_if_exists_add(env, argv[i]) == -1)
			{
				ft_putstr_fd(2, "System error\n");
				ms_exit = 1;
				return ;
			}
			else
			{
				ft_putstr_fd(2, "export: '");
				ft_putstr_fd(2, argv[i]);
				ft_putstr_fd(2, ": not a valid identifier");
				ms_exit = 1;
			}	
		}
		i++;
	}
}
