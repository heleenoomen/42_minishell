/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 18:47:58 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 12:17:48 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_to_temp(t_env_hash **temp, t_env_hash **table_ptrs, int l, int r)
{
	int	i;

	dprintf(2, "sizeof temp[0] = %lu\n", (sizeof(temp[0]) / sizeof(t_env_hash *)));
	return ;
	i = 0;
	while (i <= r)
	{
		temp[i] = table_ptrs[l + i];
		i++;
	}
}

int	make_temps(t_env_hash **temps[2], int size_t1, int size_t2)
{
	temps[0] = malloc(size_t1 * sizeof(t_env_hash *));
	temps[1] = malloc(size_t2 * sizeof(t_env_hash *));
	if (temps[0] == NULL || temps[1] == NULL)
		return (-1);
	return (0);
}

int	free_temps(t_env_hash **temps[2], int ret)
{
	(void) temps;
	return (ret);
}

void	set_vars(int i[3], int l)
{
	i[0] = 0;
	i[1] = 0;
	i[2] = l;
}

void	add_leftovers(t_env_hash **table_ptrs, t_env_hash **temp, int i, int end)
{
	int	k;

	k = 0;
	while (i < end)
	{
		table_ptrs[k] = temp[i];
		i++;
		k++;
	}
}

int		ms_merge(t_env_hash **table_ptrs, int l, int m, int r)
{
	t_env_hash	**temps[2];
	int			i[3];

	if (make_temps(temps, m - l + 1, r - m) == -1)
		return (-1);
	copy_to_temp(temps[0], table_ptrs, l, m);
	return (0);
	copy_to_temp(temps[1], table_ptrs, m + 1, r);
	set_vars(i, l);
	while (i[0] < (m - l + 1) && i[1] < (r - m))
	{
		if (ft_strcmp(temps[0][i[0]]->key, temps[1][i[1]]->key) < 0) //temps[1][i[1]]->key < 0))
		{
			table_ptrs[i[2]] = temps[0][i[0]];
			i[0]++;
		}
		else
		{
			table_ptrs[i[2]] = temps[1][i[1]];
			i[1]++;
		}
		i[2]++;
	}
	add_leftovers(table_ptrs + i[2], temps[0], i[0], m - l + 1);
	add_leftovers(table_ptrs + i[2], temps[1], i[1], r - m);
	return (free_temps(temps, 0));
}
