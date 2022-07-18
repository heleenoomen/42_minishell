/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:13:58 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/18 15:15:36 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

char	**make_envp_cpy(t_env_data *env_data, char **envp, size_t size)
{
	char	**envp_cpy;
	size_t	i;

	envp_cpy = ft_calloc((size + 1) * sizeof(char *));
	if (envp_cpy == NULL)
		panic(NULL, NULL);
	i = 0;
	while (i < size)	
	{
		envp_cpy[i] = ft_strdup(envp[i])
		if (envp_cpy[i] == NULL)
			panic(NULL, env_data);
		i++;
	}
	return (envp_cpy);
}

void	fill_hash_table(t_env_data *env_data)
{
	int			key;
	size_t		i;
	t_env_node	*new;

	i = 0;
	while (i < env_data->size)
	{
		add_to_has_table(env_data, i);
		i++;
	}
}

void	init_env_data(t_env_data *env_data, char **envp)
{
	size_t	size;

	size = 0;
	while (envp[size] != NULL)
		size++;
	ft_memset(&(env_data->hash_table), 0, 27 * sizeof(t_env_node));
	env_data->size = size;
	env_data->envp = make_envp_cpy(env_data, envp, size);
	fill_hash_table(env_data);
}
	
