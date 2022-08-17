/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:59:00 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 18:43:03 by hoomen           ###   ########.fr       */
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
	env->env_hash = ft_calloc(256, sizeof(char *));
	if (env->env_hash == NULL)
		panic("System error", NULL);
	env->size = 0;
	env->free = 255;
	env->deleted = 0;
	env->cwd = getcwd(NULL, 0);
	if (env->cwd == NULL)
		panic("System error", env);
}

/* creates a minimal envorionment if minishell was not give an 
 * environment (e.g. by running minishell with env -i)
 * We assume that minishell was called from the current working
 * directory and set _= accordingly. It is beyond the scope of
 * this project to set it fully correctly.
 */
void	startup_without_environment(t_env *env)
{
	if (add_key_value_to_env(env, "PWD", env->cwd, EXPORT | VAL_DUP | KEY_DUP) == -1)
		panic("System error", env);
	if (add_string_to_env(env, "SHLVL=1", EXPORT) == -1)
		panic("System error", env);
	if (add_key_value_to_env(env, "_=", env->cwd, EXPORT | KEY_DUP) == -1)	
		panic("System error", env);
}

/* increases the SHLVL (shell level) variable by one. If not specified or 0
 * or invalid, sets SHLVL to 1.
 */
int	update_shlvl(t_env *env)
{
	t_tree_node	*node;
	int			nbr;
	char		*value;
	
	node = *(position_in_tree(&(env->tree), "SHLVL"));
	if (node == NULL)
		return (add_key_value_to_env(env, "SHLVL", "1", EXPORT | VAL_DUP | KEY_DUP));
	nbr = ft_atoi(node->value);
	if (nbr < 1)
		return (update_env_node(env, node, "1", EXPORT | VAL_DUP));
	if (nbr == 999)
	{
		if ((update_env_node(env, node, "0", EXPORT | VAL_DUP) == -1))
			return (-1);
		return (1);
	}
	value = ft_itoa(nbr + 1);
	if (value == NULL)
		return (-1);
	return (update_env_node(env, node, value, EXPORT));	
}

/*
 * initializes env struct. If no environment was given, calls
 * startup_without_environment to give minishell a minimal environment
 * cycles through envp an adds and entry to environment struct for each
 * element of envp.
 */
void	init_env(t_env *env, char **envp)
{
	int	i;

	init_env_struct(env);
	if (envp == NULL || envp[0] == NULL)
	{
		startup_without_environment(env);
		return ;
	}
	i = 0;
	while (envp[i] != NULL)
	{
		if (add_string_to_env(env, envp[i], EXPORT) == -1)
			panic("System error", env);
		i++;
	}
	if (update_shlvl(env) == -1)
		panic("System error", env);
	if (update_shlvl(env) == 1)
		write(2, WARNING_TOO_MANY_SHLVLS, ft_strlen(WARNING_TOO_MANY_SHLVLS));
	print_hash(env, 2);
}

