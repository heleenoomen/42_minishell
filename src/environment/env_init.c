/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:59:00 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/16 19:37:11 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* sets al bytes in env struct to zero
 * asks space for env->env_hash and env->envp
 * sets env->size to 0 and env->free to 255 so that env->envp and env->env_hash
 * will be always null terminated throughout the program.
 * saves cwd in env struct 
 */ 
void	init_env_struct(t_env *env)
{
	env->tree = NULL;	
	env->envp = ft_calloc(256, sizeof(char *));
	if (env->envp == NULL)
		panic("System error", env);
	env->size = 0;
	env->free = 255;
	env->cwd = getcwd(NULL, 0);
	if (env->cwd == NULL)
		panic("System error", NULL);
}

/* creates a minimal envorionment if minishell was not give an 
 * environment (e.g. by running minishell with env -i)
 * We assume that minishell was called from the current working
 * directory and set _= accordingly. It is beyond the scope of
 * this project to set it fully correctly.
 */
void	startup_without_environment(t_env *env)
{
	if (add_key_value_dup_to_env(env, "PWD", env->cwd, EXPORT) == -1)
		panic("System error", env);
	if (add_str_to_env(env, "SHLVL=1", EXPORT) == -1)
		panic("System error", env);
	if (add_key_value_dup_to_env(env, "_=", env->cwd, EXPORT) == -1)	
		panic("System error", env);
}

/* increases the SHLVL (shell level) variable by one. If not specified or 0
 * or invalid, sets SHLVL to 1.
 */
int	update_shlvl(t_env *env)
{
	t_tree_node	*node;
	
	node = find_node(env->tree, "SHLVL");
	if (node == NULL)
		return (add_key_value_dup_to_env(env, "SHLVL", "1", EXPORT));
	nbr = ft_atoi(node->value);
	if (nbr < 1)
		return (update_value_dup(node, "1", EXPORT));
	if (nbr == 999)
	{
		if (update_value_dup(node, "0", EXPORT) == -1)
			return (-1);
		return (1);
	}
	value = ft_itoa(nbr + 1);
	if (value == NULL)
		return (-1);
	return (update_value(node, value, EXPORT));		
}

/*
 * initializes env struct. If no environment was given, calls
 * startup_without_environment to give minishell a minimal environment
 * cycles through envp an adds and entry to environment struct for each
 * element of envp.
 */
void	init_env(t_env *env, char **envp)
{
	int			i;

	init_env_struct(env);
	if (envp == NULL || envp[0] == NULL)
	{
		startup_without_environment(env);
		return ;
	}
	i = 0;
	while (envp[i] != NULL)
	{
		if (add_envp_entry_to_env(env, envp[i], EXPORT) == -1)
			panic("System error", env);
		i++;
	}
	if (update_shlvl(env) == -1)
		panic("System error", env);
	if (update_shlvl(env) == 1)
		write(2, WARNING_TOO_MANY_SHLVLS, ft_strlen(WARNING_TOO_MANY_SHLVLS));
}

