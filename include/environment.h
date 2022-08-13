/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/13 18:25:27 by hoomen           ###   ########.fr       */
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

/*deconstructor*/
void	clear_env_data(t_env *env);

/*initializes env struct*/
void	init_env_struct(t_env *env);

/*constructor for array of key-value pairs*/
t_env_pair	*construct_pairs(void);

/*resize array of key-value pairs*/
int	resize_arr_pairs(t_env *env);

/*add new key-value pair to env struct array of pairs*/
void	add_pair(t_env *env, t_env_pair new_pair, char *s);

/*make new key and value pair from input or envp string*/
char	*make_key_and_value(char *s, char **value, char **ptr_equalsign);

/*initialize environment at initialization of minishell*/
void	init_env(t_env *env, char **envp);

/*update_env.c
 * functions update environment structure when a value to an * existing key is changed by a builtin*/
int		update_arr_pairs(t_env *env, char *key, char *new_value);
int		update_envp(t_env *env, char *key, char *new_value);
int		update_env(t_env *env, char *key, char *new_value);

#endif
