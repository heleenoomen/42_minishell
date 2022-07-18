/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:02:12 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/18 15:15:26 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

void	clear_list(t_env_node **head)
{
	t_env_node	*trav;

	trav = *head;
	if (trav == NULL)
		return ;
	while (trav != NULL)
	{
		clear_list(&(trav->next));
		free(trav);
	}
	*head = NULL;
}

void	free_envp(t_env_data *env_data)
{
	size_t	i;
	char	**envp;	
	
	i = 0;
	envp = env_data->envp;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	clear_env_data(t_env_data *env_data)
{
	int			i;
	t_env_node	*trav;

	i = 0;
	while (i < 53)
	{
		clear_list(&(env_data->hash_table[i]));
		i++;
	}
	free_envp(env_data);
}


