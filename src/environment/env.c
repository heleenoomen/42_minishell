/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:44:42 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/13 14:50:41 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

/*usage: at exit minishell*/
void	clear_env_data(t_env *env)
{
	int	i;

	if (env == NULL)
		return ;
	i = 0;
	while (i < env->size)
	{
		free(env->arr_pairs[i].key);
		free(env->arr_pairs[i].value);
		i++;
	}
	free(env->arr_pairs);
	free(env->cwd);
}

/*usage: initialization of minishell only*/
t_env_pair	*construct_pairs(void)
{
	t_env_pair	*arr_pairs;

	arr_pairs = ft_calloc(256, sizeof(t_env_pair));
	return (arr_pairs);
}

/*usage: initialization of minishell, builtins*/
/*returns 0 on succes, 1 on error. All errors sytem errors*/
int	resize_arr_pairs(t_env *env)
{
	t_env_pair	*new_arr;
	int			i;
	
	if (env->size >= INT_MAX - 256)
		return (1);
	new_arr = ft_calloc((env->size + 256), sizeof(t_env_pair));
	if (new_arr == NULL)
		return (1);
	i = 0;
	while (i < env->size)
	{
		new_arr[i] = env->arr_pairs[i];
		i++;
	}	
	free(env->arr_pairs);
	env->arr_pairs = new_arr;
	env->size += 256;
	env->free = 256;
	return (0);
}

int	resize_envp(t_env *env)
{
	char	**new_envp;
	int	i;

	new_envp = ft_calloc((env->size), sizeof(char *));
	if (new_envp == NULL)
		return (1);
	i = 0;
	while (i < env->size - 256)
	{
		new_envp[i] = env->envp[i];
		free(env->envp[i]);
		i++;
	}
	while (i < 256)
	{
		new_envp[i] = NULL;
		i++;
	}
	free(env->envp);
	env->envp = new_envp;
	return (0);
}
	
	
/*usage: initialization of minishell, builtins*/
void	add_pair(t_env *env, t_env_pair new, char *s)
{
	if (env->free == 0)
	{
		if (resize_arr_pairs(env) == 1)
			panic("System error", env);
		if (resize_envp(env) == 1)
			panic("System error", env);
	}
	env->envp[env->size] = ft_strdup(s);
	if (env->envp[env->size] == NULL)
		panic("System error", env);
	env->arr_pairs[env->size].key = new.key;
	env->arr_pairs[env->size].value = new.value;
	env->arr_pairs[env->size].export_flag = new.export_flag;
	env->size++;
	env->free--;
}	

/*initialization of minishell only*/
void	init_env_struct(t_env *env)
{
	ft_memset(env, 0, sizeof(t_env));
	env->arr_pairs = construct_pairs();
	if (env->arr_pairs == NULL)
		panic("System error", env);
	env->envp = ft_calloc(256, sizeof(char *));
	if (env->envp == NULL)
		panic("System error", env);
	env->size = 0;
	env->free = 256;
}

/*usage: initialization of minishell, builtins*/
char	*make_key_and_value(char *s, char **value, char **ptr_equalsign)
{
	char	*end_pointer;

	end_pointer = s;
	while (*end_pointer != '=')
		end_pointer++;
	*ptr_equalsign = end_pointer;
	*end_pointer = '\0';
	*value = end_pointer + 1;
	return (s);
}

void	free_minimal_envp(char ***min_envp)
{
	free((*min_envp)[0]);
	free((*min_envp)[1]);
	free((*min_envp)[2]);
	free(*min_envp);
	*min_envp = NULL;
}

char	**make_minimal_envp(t_env *env)
{
	char	**envp;

	envp = ft_calloc(4, sizeof(char *));
	if (envp == NULL)
		panic("System error", NULL);
	envp[0] = ft_strjoin("PWD=", env->cwd);
	envp[1] = ft_strdup("SHLVL=1");
	if (envp[0] == NULL || envp[1] == NULL)
	{
		free_minimal_envp(&envp);
		panic("System error", NULL);
	}
	envp[2] = ft_strjoin("_=", env->cwd);
	return (envp);
}

int		get_key_index(t_env *env, char *key)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (strcmp(env->arr_pairs[i].key, key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	set_cwd(t_env *env)
{
	env->cwd = getcwd(NULL, 0);
	if (env->cwd == NULL)
		panic("System error", NULL);
}

void	update_shlvl(t_env *env)
{
	int		i;
	int		nbr;
	char	*new_value;
	char	*new_envp_entry;
	char	*warning = "Warning: Shell level (1000)\
						to high, resetting to 0\n";

//	dprintf(2, "in update_shlvl\n");
	i = get_key_index(env, "SHLVL");
	if (i == -1)
	{
		dprintf(2, "SHLVL not found\n");
		return ;
	}
	nbr = ft_atoi(env->arr_pairs[i].value);
//	dprintf(2, "nbr = %i\n", nbr);
	if (nbr == 1000)
	{
		write(2, warning, ft_strlen(warning)); 
		nbr = 0;
	}
	new_value = ft_itoa(nbr + 1);
//	dprintf(2, "new_value = %s\n", new_value);
	if (new_value == NULL)
	{
		perror("env");
		ms_exit_status = ENOMEM;
	}
	free(env->arr_pairs[i].value);
	env->arr_pairs[i].value = new_value;
//	dprintf(2, "env->arr_pairs[i].value = %s\n", env->arr_pairs[i].value);
//	dprintf(2, "i = %i\n", i);
	new_envp_entry = ft_strjoin(env->arr_pairs[i].key, "=");
	if (new_envp_entry == NULL)
		panic("System error", env);
	new_envp_entry = ft_strjoin(new_envp_entry, env->arr_pairs[i].value);
	if (new_envp_entry == NULL)
		panic("System error", env);
	free(env->envp[i]);
	env->envp[i] = new_envp_entry;
}

		
void	init_env(t_env *env, char **envp)
{
	int			i;
	t_env_pair	new;
	char		*value;
	char		*ptr_equalsign;
	bool		minimal;

	init_env_struct(env);
	set_cwd(env);
	i = 0;
	if (envp[i] == NULL)
	{
		envp = make_minimal_envp(env);//("No environment", NULL);
		minimal = 1;
	}
	else
		minimal = 0;
	while (envp[i] != NULL)
	{
		new.key = ft_strdup(make_key_and_value(envp[i], &value, &ptr_equalsign));
		new.value = ft_strdup(value);
		if (new.key == NULL || new.value == NULL)
			panic("System error", env);
		new.export_flag = 1;
		*ptr_equalsign = '=';
		add_pair(env, new, envp[i]);
		i++;
		if (i == INT_MAX)
			panic("System error", env);
	}
	if (minimal)
		free_minimal_envp(&envp);
	else
		update_shlvl(env);
}

//int	main(int argc, char **argv, char **envp)
//{
//	t_env	env;
//
//	init_env(&env, envp);
//	int i = 0;
//	while (i < env.size)
//	{
//		printf("--------------\n");
//		printf("key = %s\n", env.arr_pairs[i].key);
//		printf("value = %s\n", env.arr_pairs[i].value);
//		printf("export flag = %d\n", env.arr_pairs[i].export_flag);
//		printf("--------------\n");
//		i++;
//	}
//	clear_env_data(&env);
//	system("leaks a.out");
//}
