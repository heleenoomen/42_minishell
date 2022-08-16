/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:00:45 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 10:04:10 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//bool	is_valid_unset(char *s)
//{
//	size_t	i;
//
//	if (first_char_not_valid(s[0]))
//		return (false);
//	i = 0;
//	while (s[i])
//	{
//		if (!ft_isalnum(s[i]) && s[i] != '_')
//			return (false);
//		if (i == (size_t) -1)
//			return (false);
//		i++;
//	}
//}
//
//void	free_entry(t_env *env, int i)
//{
//	free(env->envp[i]);
//	env->env[i] = NULL;
//	free(env->env_hash[i].key);
//	env->env_hash[i].key = NULL;
//	free(env->env_hash[i].value);
//	env->env_hash[i].value = NULL;
//}
//
//void	shrink_env_us(t_env *env, int deleted)
//{
//	int	src;
//	int	dst;
//
//	clear_sorted(env);
//	src = 0;
//	while (src < env->size && env->envp[src] != NULL)
//		src++;
//	dst = src;
//	while (src < env->size)
//	{
//		if (env->envp[src] == NULL)
//		{
//			src++;
//			sort_hash_entry(env, src);
//		}
//		else
//		{
//			env->envp[dst] = env->envp[src];
//			env->env_hash[dst].key = env->env_hash[src].key;
//			env->env_hash[dst].value = env->env_hash[src].value;
//			sort_hash_entry(env, dst);
//			src++;
//			dst++;
//		}
//	}
//	env->size -= deleted;
//	env->free += deleted;
//	if (env->free > 256)
//		shrink_env(env);
//}

void	mini_unset(char **argv, t_env *env)
{
//	int	i;
//	int	key_ind;
//	int	deleted;

	(void) argv;
	sort_env2(env);
//	return ;
//	i = 1;
//	deleted = 0;
//	while (argv[i] != NULL)
//	{
//		if (!is_valid_unset(argv[i]))
//		{
//			ft_putstr_fd(2, "unset: ");
//			ft_putstr_fd(2, argv[i]);
//			ft_putstr_fd(2, ": invalid identifier");
//			ms_exit = 1;
//		}
//		else
//		{
//			key_ind = key_index(argv[i]);
//			if (key_ind != -1)
//			{
//				free_entry(env, key_ind);
//				deleted++;
//			}
//		i++;
//	}
//	if (env_changed, deleted)
//		shrink_env_us(env, deleted);
}
