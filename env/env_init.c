/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:13:58 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/18 19:36:00 by hoomen           ###   ########.fr       */
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
		envp_cpy[i] = ft_strdupenvp[i])
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

t_env_pair	*make_pair(t_env_data *env_data, char *s)
{
	t_env_pair	*new_pair;

	new_pair = malloc(sizeof(new_pair));
	if (new_pair == NULL)
		panic("system error");
	new_pair->key = make_key(env_data, s);
	new_pair->value = make_value(env_data, s);
	return (value);

void	init_env_data(t_env_data *env_data, char **envp)
{
	int			i;
	t_env_pair	*new_pair;
	
	env_data->unsorted = NULL;
	env_data->unsor_last = NULL;
	ft_memset(&(env_data->hash_table), 0, 27 * sizeof(t_env_node));
	while(envp[i])
	{
		new_pair = make_pair(env_data, envp[i]);
		add_to_unsorted(env_data, new_pair);
		add_to_hash_table(env_data, new_pair);
		i++;
	}
}
	
