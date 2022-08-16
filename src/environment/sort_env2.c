/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:22:59 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 12:26:54 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quicksort(t_env_hash **arr_ptrs, int l, int r);

void	swap_ptrs(t_env_hash **arr_ptrs, int i, int j)
{
	t_env_hash *temp;

	temp = arr_ptrs[i];
	arr_ptrs[i] = arr_ptrs[j];
	arr_ptrs[j] = temp;
}

void	repeat(t_env_hash **arr_parts, int i, int l, int r)
{
	if (i != l)
		quicksort(arr_parts, l, i - 1);
	if (i != r)
		quicksort(arr_parts, i + 1, r);
}

void	quicksort(t_env_hash **arr_ptrs, int l, int r)
{
	int				v;
	t_env_hash		*temp;
	int				i;
	int				j;

	if (l >= r)
		return ;
	i = l;
	j = r;
	v = arr_ptrs[r]->key[0];
	while (1)
	{
		while (arr_ptrs[i]->key[0] < v && i != r)
			i++;
		while (arr_ptrs[j]->key[0] >= v && j != l)
			j--;
		if (i >= j)
			break ;
		swap_ptrs(arr_ptrs, i, j);
	}
	temp = arr_ptrs[i];
	arr_ptrs[i] = arr_ptrs[r];
	arr_ptrs[r] = temp;
	repeat(arr_ptrs, i, l, r);
}

int	sort_env2(t_env *env)
{
	t_env_hash	**arr_ptrs;
	int			i;
	int			j;
	int			k;

	arr_ptrs = malloc(env->size * sizeof(t_env_hash *));
	i = 0;
	j = 0;
	while (i < env->size)
	{
		if (env->envp[i] != NULL)
		{
			arr_ptrs[j] = &(env->env_hash[i]);
			i++;
			j++;
		}
		else
			i++;
	}
	quicksort(arr_ptrs, 0, env->size - 1);
	
	i = 0;
	while (i < env->size)
	{
		ft_putstr_fd(arr_ptrs[i]->key, 2);
		write(2, "\n", 1);
		i++;
	}
	free(arr_ptrs);
	return (0);
}
