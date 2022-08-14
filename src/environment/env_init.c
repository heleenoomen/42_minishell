/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 14:59:00 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 12:49:17 by hoomen           ###   ########.fr       */
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
	ft_memset((void *)env, 0, sizeof(env));
	env->env_hash = ft_calloc(256, sizeof(t_env_hash);
	if (env->env_hash == NULL)
		panic("System error", env);
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
	int	ret;

	if (add_key_value_pair_to_env(env, "PWD", env->cwd, EXPORT) == -1)
		panic("System error", env);
	if (add_envp_entry_to_env(env, "SHLVL=1", EXPORT) == -1)
		panic("System error", env);
	if (add_envp_entry_to_env(env, "_=", env->cwd, EXPORT) == -1)	
		panic("System error", env);
}

void	set_shlvl(t_env *env, char *value, int i)
{
	if (change_value(env, value, "SHLVL", i) == -1)
		panic("System error", env);
}

/* increases the SHLVL (shell level) variable by one. If not specified or 0
 * or invalid, sets SHLVL to 1.
 */
void	update_shlvl(t_env *env)
{
	int		i;
	char	*value;
	int		nbr;

	i = key_index(env, "SHLVL");
	if (i = -1)
	{
		if (add_key_value_pair_to_env(env, "SHLVL", "1") == -1)
			panic("System error", env);
	}
	nbr = ft_atoi(env_hash[i].value);
	if (nbr < 1)
		set_shlvl(env, "1", SHLVL, i);
	if (nbr == 999)
	{
		set_shlvl(env, "0", SHLVL, i);
		write(2, WARNING_TOO_MANY_SHLVLS, ft_strlen(WARNINGi_TOO_MANY_SHLVLS));
	}
	value = ft_itoa(nbr + 1);
	if (value == NULL)
		panic("System error", env);
	if (change_value_existing_key(env, value, "SHLVL", i) == -1)
		panic("System error", env);
	free(value);
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
		if (add_envp_entry_to_env(env, env[i], EXPORT) == -1)
			panic("System error", env);
		i++;
	}
	if (update_shlvl(env) == -1)
		panic("System error", env);
}

