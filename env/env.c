/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:44:42 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/19 11:15:36 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_env_pair
{
	char	*key;
	char	*value;
	bool	export_flag;
}			t_env_pair;

typedef struct s_env
{
	t_env_pair	*arr_pairs;
	int			size;
	int			free;
}				t_env;

t_env_pair	*construct_pairs(void)
{
	t_env_pair	*arr_pairs;

	arr_pairs = ft_calloc(255 * sizeof(t_env_pair));
	return (arr_pairs);
}

int	resize_arr_pairs(t_env *env)
{
	t_env_pair	*new_arr;
	int			i;
	
	if (i >= MAX_INT - 255)
		return (1);
	new_arr = ft_calloc(env->size + 255);
	if (new_arr == NULL)
		return (1);
	i = 0;
	while (i < env->size)
	{
		new_arr[i] = env->arr_pairs[i];
		i++;
	}
	free(env->arr_pairs);
	env->arr_pairs = env->new_arr;
	env->size += 255;
	env->free = 255;
	return (0);
}

void	add_pair(t_env *env, t_env_pair *new);	
{
	env->arr_pairs[size] = new;
	env->size++;
	env->free--;
}	

void	init_env_struct(t_env *env)
{
	ft_memset(env, 0, sizeof(t_env));
	env->arr_pairs = construct_pairs();
	if (env->arr_pairs == NULL)
		panic("System error", env);
	env->size = 0;
	env->free = 255;
}

char	*make_key_and_value(char *s, char **value)
{
	char	*end_pointer;
	size_t	len;

	len = ft_strlen(s);
	s[len - 1] = '\0';
	end_pointer = s;
	while (*s != '=')
		end_pointer++;
	*end_pointer = '\0';
	*value = end_pointer + 2;
	return (s);
}

void	init_env(t_env *env, char **envp)
{
	int			i;
	t_env_pair	*new;
	char		*value;

	init_env_struct(env);
	i = 0;
	while (envp[i] != NULL)
	{
		new = ft_calloc(sizeof(t_env_pair));
		if (new == NULL)
			panic("System error", env);
		new->key = ft_strdup(make_key_and_value(envp[i], &value);
		new->value = ft_strudp(value);
		if (new->key == NULL || new->value == NULL)
			panic("System error", env);
		new->export_flag = 1;
		add_pair(env, new);
		i++;
		if (i == MAX_INT)
			panic("System error", env);
	}
}

