/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:44:34 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/18 19:35:56 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

typedef struct s_env_pair
{
	char		*key
	char		*value
	bool		export_flag;
	//s_env_pair	*next;
}				t_env_pair;

/* t_env_data stores environment data
 * size = items in environment list
 * hash table keys:
 * 		A-Z = 0-25
 * 		_   = 26
 * 		a-z = 27-52 */
typedef struct s_env_data
{
	t_env_node	*unsorted;
	t_env_node	*unsor_last;
	t_env_node	hash_table[53];
}				t_env_data;



/* clear_env_data.c */
void		clear_env_data(t_env_data *env_data);
void		free_envp(t_env_data *env_data);
void		clear_list(t_env_data **head);

/* env_init.c */
void		init_env_data(t_env_data *env_data, char **envp);
void		fill_hash_table(t_env_data *env_data);
char		**make_envp_cpy(t_env_data *env_data, char **envp, size_t size);

/* add_to_has_table.c */
void		add_to_hash_table(t_env_data *env_data, size_t i);
t_env_node	*new_env_node(t_env_data *env_data, size_t, i);
int			get_key(char *s);

#endif
