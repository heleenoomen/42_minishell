/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 13:16:07 by hoomen            #+#    #+#             */
/*   Updated: 2022/09/08 17:48:18 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* traverses the environment tree. Prints everything on the left of branch first,
 * the prints the branch itself: "declar -x " prefix, followed by the key. If
 * value is not NULL, value is printed in between dubble quotes. Finally, a new-
 * line is printed. Then everything to the right is printed.
 */
void	print_tree_mini_exp(t_tree_node *branch)
{
	if (branch == NULL)
		return ;
	print_tree_mini_exp(branch->left);
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(branch->key, 1);
	if (branch->value != NULL)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(branch->value, 1);
		write(1, "\"", 1);
	}
	write(1, "\n", 1);
	print_tree_mini_exp(branch->right);
}
		

/* checks if the first char of the key is either alphabetical or underscore
 * if not, the key or key value pair is not valid
 */
bool	first_char_valid(char c)
{
	if (c >= 'a' && c <= 'z')
		return (true);
	if (c >= 'A' && c <= 'Z')
		return (true);
	if (c == '_')
		return (true);
	return (false);
}

/* checks if argument for export is valid. Before the '=' sign, only alphanumerical
 * characters and underscores are permitted. After the equal sign, all ascii-chars are
 * permitted. If the length of s is size_t max or bigger, returns false.
 */
bool	is_valid(char *s)
{
	size_t	i;
	
	i = 0;
	if (!first_char_valid(s[i]))
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
	i++;
	while (s[i])
	{
		if (i == (size_t) -1)
			return (false);
		if ((int) s[i] < 0 || (int) s[i] > 256)
			return (false);
		i++;
	}
	return (true);
}

void	mini_export_invalid_identifier(char *s)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": not a valid identifier", 2);
	g_global_exit_status = 1;
}

void	mini_export(t_list *cmd, t_env *env)
{
	int		i;
	int		argc;
	char	**argv;

	argv = list_to_argv(cmd, &argc);
	if (argv == NULL)
		return (print_error_builtins("export", SYS_ERR));
	if (argc == 1)
	{
		print_tree_mini_exp(env->tree);
		return ;
	}
	i = 1;
	while (argv[i] != NULL)
	{
		if (is_valid(argv[i]))
		{
			if (update_env_string(env, argv[i], EXPORT | KEY_DUP | VAL_DUP) == -1)
			{
				g_global_exit_status = ENOMEM;
				return (print_error_builtins("cd", SYS_ERR));
			}
		}
		else
			mini_export_invalid_identifier(argv[i]);
		i++;
	}
	free(argv);
}

