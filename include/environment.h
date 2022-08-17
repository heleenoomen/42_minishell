/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 10:59:21 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/17 18:42:21 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include<limits.h>

/* entries in the hash table. Hash tables' only function is to imitate the order
 * bash puts the env variables in when you call "env" command without options*/
typedef struct s_env_hash
{
	char	*key;
	char	*value;
	bool	for_export;
}			t_env_hash;

/* tree structure where key/value pairs of environment are stored */
typedef struct s_tree_node
{
	char				*key;
	char				*value;
	bool				for_export;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}						t_tree_node;

/* env structure stores a pointer to the key and the current working directory
 * also stores a hash table (array of t_env_hash structs) that grows in size when
 * needed. Struct keeps track of how many entries in hash table, how much entries are
 * free and how much entries were deleted
 */
typedef struct s_env
{
	t_tree_node	*tree;
	int			size;
	int			free;
	int			deleted;
	t_env_hash	*env_hash;	
	char		*cwd;
}				t_env;

/* flags for the functions that add new key/value pairs to the environment. 
 * EXPORT = variable should be marked for export
 * KEY_DUP = key is a pointer to a string that should be duplicated (malloced)
 * VAL_DUP = id for value
 * VAL_OVERW = when updating an existing key, overwrite the existing value
 */
# define EXPORT 0b1
# define KEY_DUP 0b10
# define VAL_DUP 0b100
# define VAL_OVERW 0b1000

# define WARNING_TOO_MANY_SHLVLS "Minishell: Warning: level of shells (1000) too high, resetting to 0"

/* tree2.c */
t_tree_node	**position_in_tree(t_tree_node **tree, char *key);
t_tree_node	*new_node(char *key, char *value, short flags);
void		add_node(t_tree_node **tree, t_tree_node *new_node);
int			del_tree_node(t_tree_node **tree, t_tree_node **node, char *key, int ret);
void		free_tree(t_tree_node **tree);

/* env_init.c */
void		init_env_struct(t_env *env);
void		startup_without_environment(t_env *env);
int			update_shlvl(t_env *env);
void		init_env(t_env *env, char **envp);

/* add_to_env2.c */
int			add_to_hash(t_env *env, char *key, char *value, short flags);
int			add_to_tree(t_env *env, char *key, char *value, short flags);
int			add_key_value_to_env(t_env *env, char *key, char *value, short flags);
char		*manipulate_ptrs(char *s, char **value_ptr);
int			add_string_to_env(t_env *env, char *s, short flags);

/* update_env2.c */
void		update_node(t_tree_node *node, char *value, short flags);
void		update_hash(t_env *env, char *key, char *value, short flags);
int 		update_env(t_env *env, char *key, char *value, short flags);
int 		update_env_node(t_env *env, t_tree_node *node, char *value, short flags);

/* remove_from_env2.c */
int			remove_from_env(t_env *env, char *key);

/* env_resize2.c */
void		copy_hash(t_env_hash *new_hash, t_env_hash old_hash);
int			grow_env_hash(t_env *env);
void		shrink_env_hash(t_env *env);
int			cleanup_env_hash(t_env *env);

/* env_utils2.c */
void		clear_env(t_env *env);
int			ft_strdup_int(char **dup, char *s);
int			del_key_value(char *key, char *value, short flags, int ret);
char		*find_value(t_env *env, char *key);

/* make_envp.c */
char		**free_strarr(char **strarr);
int			triple_strjoin_int(char **triple, char *s1, char *s2, char *s3);
char		**make_envp(t_env *env);

/* print_tree.c */
void		print_tree(t_tree_node *node, int fd);
void		print_hash(t_env *env, int fd);
#endif

