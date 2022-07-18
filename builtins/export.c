
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:10:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/17 15:58:02 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(t_env_data *env_data)
{
	int			i;
	t_env_node	*trav;

	i = 0;
	while (i < 53)
	{
		if (env_data->hash_table[i] != NULL)
		{
			trav = hash_table[i];
			while (trav != NULL)
			{
				write(1, "declare -x ", 11);
				write(1, trav->env_var, ft_strlen(trav->env_var);
				write(1, "\n", 1);
				trav = trav->next;
			}
		}	
		i++;
	}
}

int		var_is_valid(const char *s)
{
	if (s[0] >= 'A' && s[0] <= 'Z')
		return (1);
	if (s[0] >= 'a' && s[0] <= 'z')
		return (1);
	if (s[0] == '_')
		return (1);
	return (0);
}

void	export_item(char *s, t_env_data *env_data)
{
	char	**envp_new;
	size_t	i;
	
	if (!ft_strchr(s, '=')
		return ;
	envp_new = ft_calloc(env_data->size + 2, sizeof(char *));
	if (envp_new == NULL)
		panic(NULL, env_data);
	i = 0;
	while (i < env_data->size)
	{
		envp_new[i] = env_data->envp[i];
		i++;
	}
	envp_new[i] = ft_strdup(s);
	if (envp_new[i] == NULL)
		panic(NULL, env_data);
	free_envp(env_data);
	env_data->envp = envp_new;
	env_data->size++;
	add_to_hash_table(env_data, size - 1);
}	

void	export(int argc, char **argv, t_env_data *env_data)
{
	int	i;

	if (argc == 1)
		print_env_data(env_data);	
	i = 0;
	while (argv[i] != NULL)
	{
		if (!var_is_valis(argv[i])
		{
			perror(argv[i]);
			exit_status = 1;
		}
		else
			export_item(argv[i], env_data);
		i++;
	}
}
