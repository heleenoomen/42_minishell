/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort_arr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:33:09 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/15 19:28:40 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_merge(t_env_hash **table_ptrs, int l, int m, int r)
{
	int	i;
	int	j;
	int	k;
	int n1;
	int	n2;
	t_env_hash **left;
	t_env_hash **right;	

	n1 = m - l + 1;
	n2 = r - m;
	left = malloc(sizeof(t_env_hash *) * n1);
	if (left == NULL)
		return (-1);
	right = malloc(sizeof(t_env_hash *) * n2);
	if (right == NULL)
	{
		free(left);
		return (-1);
	}
	i = 0;
	while (i < n1)
	{
		left[i] = table_ptrs[i];
		i++;
	}
	j = 0;
	while (j < n2)
	{
		right[j] = table_ptrs[j];
		j++;
	}
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (ft_strcmp(left[i]->key, right[i]->key) < 0)
		{
			table_ptrs[k] = left[j];
			i++;
		}
		else
		{
			table_ptrs[k] = right[i];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		table_ptrs[k] = left[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		table_ptrs[k] = right[i];
		j++;
		k++;
	}
}	

int	ms_mergesort(t_env_hash **table_ptrs, int l, int r)
{
	int	mid;

	if (l < r)
	{
		mid = l + ((r - l) / 2);
		if (ms_mergesort(table_ptrs, l, m) == -1)
			return (-1);
		if (ms_mergesort(table_ptrs, m + 1, r));
			return (-1);
		if (ms_merge(table_ptrs, l, m, r))
			return (-1);
	}
}

int	mergesort_env(t_env *env)
{
	t_env_hash	**table_ptrs;
	int			i;
	
	table_ptrs = malloc(env->size * sizeof(t_env_hash *));
	if (tabl_ptrs == NULL)
		return (-1);
	i = 0;
	while (i < env->size)
	{
		table_ptrs[i] = &(env->env_hash[i]);
		i++;
	}
	return (ms_mergesort(table_ptrs, 0, env->size));
}
