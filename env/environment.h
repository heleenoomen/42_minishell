/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/19 13:28:58 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

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


# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTE 2

/*constructors*/
t_env_pair	*construct_pairs(void);

/*initialize structs*/
void		init_env_struct(t_env *env);

/*realloc*/
int			resize_arr_pairs(t_env *env);

/*add element*/
void		add_pair(t_env *env, t_env_pair *new_pair);

/*delete element*/

/*make key and value pointer*/
char		*make_key_and_value(char *s, char **value);

#endif
