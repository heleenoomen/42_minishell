
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 13:10:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/17 15:58:02 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/* add to minishell.h:
 *
 *	typedef struct s_envp
 *	{
 *		size_t		size;
 *		char		**envp;
 *		char		**envp_hash[26];
 *	} 				t_envp;
 *
 *	#define PREFIX_PRINT_ENVP "declare -x "
 *	#define PREFIX_PRINT_ENVP_LEN 11
 *
 */

void	print_envp(t_envp *envp)
{
	int		i;

	i = 0;
	while (envp->envp[i] != NULL)
	{
		write(1, "declare -x ", 11);
		write(1, envp[i], ft_strlen(envp[i]);
		write(1, "\n", 1);
		i++; 
	}
}

void	export(int argc, char **argv, t_envp *envp)
{
	t_envp	*envp;
	char 	**envp_new;
	int		i;
	
	if (argc == 1)
		print_envp(envp);`	
	envp_new = ft_calloc(envp->size + 1, sizeof(char *));
	if (envp_new == NULL)
		panic("malloc failed", envp);
	i = 0;
	while (i < envp->size)
	{
		envp_new[i] = envp->envp[i];
		i++;
	}
	envp_new[i] = ft_strdup(argv[1]);
	if (envp_new[i] == NULL)
		panic("malloc failed", envp);
	free(envp->envp);
	envp->envp = envp_new;
	envp->size++;
}	
