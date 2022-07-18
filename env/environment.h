/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_environment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 13:44:34 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/18 15:16:49 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

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
