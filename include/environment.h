/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 12:53:38 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include<limits.h>

typedef struct env_hash
{
	char	*key;
	char	*value;
	bool	for_export;
}			t_env_hash;

typedef struct s_env
{
	t_env_hash	*env_hash;
	int			size;
	int			free;
	char		**envp;
	char		*cwd;
}				t_env;


# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTE 2

# define EXPORT 1
# define NO_EXPORT 0

# define UNKNOWN -1

# define WARNING_TOO_MANY_SHELLS "Minishell: Warning: level of shells (1000) too high, resetting to 0"

/* env_init.c */
void	init_env_struct(t_env *env);
void	startup_without_environment(t_env *env);
void	set_shlvl(t_env *env, char *value, int i);
void	update_shlvl(t_env *env);
void	init_env(t_env *env, char **envp);

/* add_to_env.c */
static void	manipulate_ptrs(char *envp_entry, char **value_ptr);
static int	key_value_to_envp_entry(char **envp_entry, char *key, char *value);
int			change_value(t_env *env, char *value, char *key, int i);
int			add_envp_entry_to_env(t_env *env, char *envp_entry, bool for_export);
int			add_key_value_pair_to_env(t_env *env, char *key, char *value, bool for_export);

/* resize_env.c */
static int	resize_hashtable(t_env *env);
static int	resize_envp(t_env *env);
int			resize_env(t_env *env);

/* env_utils.c */
void		clear_env(t_env *env);
int			get_key(t_env *env, char *key);

