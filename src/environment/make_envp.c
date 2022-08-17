/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:29:15 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 16:53:33 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_strarr(char **strarr)
{
	int	i;

	i = 0;
	while (strarr[i] != NULL)
	{
		free(strarr[i]);
		i++;
	}
	free(strarr);
	return (NULL);
}

int		triple_strjoin_int(char **triple, char *s1, char *s2, char *s3)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if (join == NULL)
		return (-1);
	*triple = ft_strjoin(join, s3);
	free(join);
	if (*triple == NULL)
		return (-1);
	return (0);
}

char	**make_envp(t_env *env)
{
	char	**envp;
	int		i;
	int		j;

	envp = ft_calloc((env->size + 1), sizeof(char *));
	if (envp == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < env->size)
	{
		if (env->env_hash[i].key != NULL)
		{
			if (env->env_hash[i].value == NULL)
			{
				if (ft_strdup_int(envp + j, env->env_hash[i].key))
					return (free_strarr(envp));
			}
			else
			{
				if (triple_strjoin_int(envp + j, env->env_hash[i].key, "=",
							env->env_hash[i].value) == -1)
					return (free_strarr(envp));
			}
			j++;
		}
		i++;
	}
	return (envp);
}

