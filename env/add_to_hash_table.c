/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_hash_table.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:54:12 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/18 15:15:14 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

/* A - Z = 0 - 25
 * _ = 26
 * a - z = 27 - 52
 */
int	get_key(char *s)
{
	if (s[0] == '_')
		return (26);
	if (s[0] >= 'A' && s[0] <= 'Z')
		return (s[0] - 'A');
	if (s[0] >= 'a' && s[0] <= 'z')
		return (s[0] - 'a' + 27);
}
	
t_env_node	*new_env_node(t_env_data *env_data, size_t i)
{
	t_env_node	*new;

	new = malloc(sizeof(t_env_node));
	if (new == NULL)
		panic(NULL, env_data);
	new->env_var = env_data->envp[i];
	new->next = NULL;
	return (new);
}

void	add_to_hash_table(t_env_data *env_data, size_t i)
{
	int			key;
	t_env_node	*new;
	t_env_node	*trav;

	key = get_key(env_data->envp[i]);	
	new = new_env_node(env_data, i);
	insert_in_hash_table(new, env_data, key);
	trav = env_data->hash_table[key];
	while (trav != NULL)
	{
		if (ft_strcmp(new->env_var, trav->env_var) < 0)
		{
			new->next = trav;
			trav = new;
			return ;
		}
		trav = trav->next;
	}
	trav = new;
}	

