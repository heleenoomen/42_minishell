
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

void	export(int argc, char **argv, t_env_data *env_data)
{
	char	**envp_new;
	size_t	i;
	
	if (argc == 1)
		print_env_data(env_data);	
	envp_new = ft_calloc(env_data->size + 2, sizeof(char *));
	if (envp_new == NULL)
		panic(NULL, env_data);
	i = 0;
	while (i < env_data->size)
	{
		envp_new[i] = env_data->envp[i];
		i++;
	}
	envp_new[i] = ft_strdup(argv[1]);
	if (envp_new[i] == NULL)
		panic(NULL, env_data);
	free_envp(env_data);
	env_data->envp = envp_new;
	env_data->size++;
	add_to_hash_table(env_data, size - 1);
}	

