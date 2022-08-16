/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:29:41 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 13:51:55 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	is_valid_us(char *s)
{
	size_t	i;

	if (first_char_not_valid(s[0])
		return (fasle);
	i = 0;
	while (s[i]))
	{
	if (!ft_isalnum(s[i] && s[i] != '_'))
		return (false);
	if (i == (size_t) -1)
		return (false);
	i++;
	}
}

void	free_entry(t_env *env, int i)
{
	t_env_node	*trav;
	char		*key;
	
	key = env->env_hash[i].key;
	free(env->envp[i]);
	env->envp[i] = NULL;
	free(env->env_hash[i].key);
	env->env_hash[i].key = NULL;
	free(env->env_hash[i].value);
	env->env_hash[i].value = NULL;
	env->env_hash[i].for_export = 0;

}

void	mini_unset(char **argv, t_env *env)
{
	int	i;
	int	key_index;
	int	deleted;

	while (argv[i] != NULL)
	{
		if (!is_valid(argv[i]))
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd(": invalid identifier\n", 2);
			ms_exit = 1;
		}
		else
		{
			key_ind = key_index(argv[i]);
			if (key_ind != -1)
			{
				free_entry(env, key_ind);
				deleted++;
			}
		}
		i++;
	}
	if (deleted)
		shrink_env_us(env, deleted);
}
