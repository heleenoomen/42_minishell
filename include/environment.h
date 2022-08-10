/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/20 18:39:30 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include<limits.h>

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
	char		**envp;
}				t_env;


# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTE 2

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

#endif
