/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:04:10 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/15 13:14:28 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_hash(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 65);
	if (c >= '_')
		return (26);
	else	
		return (c - 97 + 27);
}

static void	add_to_lst(t_env_node *new, t_env_node **lst)
{
	t_env_node	*trav;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if ((*lst)->next == NULL)
	{
		if (ft_strcmp(new->entry->key, (*lst)->entry->key) < 0)
		{
			new->next = *lst;
			*lst = new;
			return ;
		}
		(*lst)->next = new;
		return ;
	}
	trav = *lst; 
	while (trav->next != NULL)
	{
		if (ft_strcmp(new->entry->key, trav->next->entry->key) < 0)
		{
			new->next = trav->next;
			trav->next = new;
			return ;
		}
		trav = trav->next;
	}
	trav->next = new;
}

/* takes as parameter the environment and the index of the hash entry to be
 * sorted. Adds the entry to the sorted hash table t_env_node->sorted
 * in which entry 0-25 corresponds to A-Z, 26 corresponds to _ and 27-52 
 * correspond to a-z.
 * Returns -1 if malloc fails. Returns 0 on success
 */
int	sort_hash_entry(t_env *env, int i)
{
	int			hash;
	char		first_char;
	t_env_node	*new;
	
	new = malloc(sizeof(t_env_node));
	if (new == NULL)
		return (-1);
	new->entry = env->env_hash + i;
	new->next = NULL;
	first_char = new->entry->key[0];
	hash = get_hash(first_char);
	add_to_lst(new, &(env->sorted[hash]));
	return (0);
}

