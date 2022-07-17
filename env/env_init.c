/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 16:55:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/17 19:22:57 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct	s_envp_node
{
	char		*env_variable;
	s_envp_node	*next;
}				t_envp_node;

typedef struct	s_envp
{
	size_t		size;
	char		**envp;
	t_envp_node	*hash;
}				t_envp;

t_envp	*make_envp(char **envp)
{
	t_envp	*envp_data;
	int		i;

	envp_data = malloc(sizeof(t_envp));
	if (envp_data == NULL)
		panic("malloc failed", NULL);
	i = 0;
	while (envp[i] != NULL)
		i++;
	envp_data->size = i;
	envp_data->envp = ft_calloc(envp->size + 1, sizeof(char *));
	envp_data->hash = NULL;
	if (envp_data->envp == NULL)
		panic("malloc failed", envp_data);
	i = 0;
	while (i < envp_data->size)
	{
		envp_data->envp[i] = ft_strdup(envp[i]);
		if (envp_data->envp[i] == NULL)
			panic("canno initialize environment, malloc failed", envp_data);
		i++;
	}
	envp_data->envp[i] = NULL;
	return (envp_data);
}

t_envp_node	*make_new_node(t_envp *envp, char *variable)
{
	t_envp_node	*new;

	malloc(sizeof(t_envp_node));
	if (new == NULL)
		panic("cannot initialize environment, malloc failed", &envp);
	new->env_variable = variable;
	new->next = NULL;
	return (new);
}

void	insert_hash_node(t_envp *envp, t_envp_node **hash, int key, char *variable)
{
	t_envp_node	*new;
	t_envp_node *head;
	t_envp_node	*previous;

	new = make_new_node(envp, variable);
	head = (*hash)[key];
	if (head == NULL)
	{
		head = new;
		return ;
	}
	while (head != NULL)
	{
		if (ft_strcmp(new->env_variable, head->env_variable) < 0)
		{
			new->next = head;
			if ((*hash)[key])->next == NULL)
				(*hash)[key] = new;
			else
				previous->next = new;
			return ;
		}
		previous = head;
		head = head->next;
	}
}

t_envp_hash	*make_hash(t_envp *envp)
{
	t_envp_node	*hash;
	t_envp_node	*temp;
	int			i;
	int			key;

	hash = ft_calloc(26 * sizeof(t_envp_node));
	if (hash == NULL)
		panic("cannot initialize environment, malloc failed", &envp);
	i = 0;
	while (i < envp->size)
	{
		key = envp[i][0] - 'A';
		insert_hash_node(envp, &hash, key, envp[i]);
		i++;
	}
	return (hash);
}

void	init_env(char **envp)
{
	t_envp		*envp;
	t_envp_node	*envp_hash;
	int			i;



	envp_hash = malloc(sizeof(t_envp_node));	
	if (envp_hash == NULL)
		panic("malloc failed");



