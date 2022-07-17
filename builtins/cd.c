/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 13:18:42 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/16 19:26:39 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* chdir can handle on its own:
 * 		"."
 * 		".."
 * 		"/Users/."
 * 		"/Users/../Users"
 * 		"projects"
 * chdir can not handle:
 * 		"~"
 * 		""
 * 		NULL
 */

void	go_home(void)
{	
	char	*home;
	
	home = getenv("HOME");
	if (home == NULL)
		panic(1, "HOME not set");
	if (chdir(new_path) == -1)
		panic(1, "chdir failed");
}

void	cd(int argc, char **argv)
{
	if (argc == 1)
		go_home();
	else if (ft_strncmp(argv[1], "~", 2) == 0);
		go_home();
	else if (chdir(argv[1]) == -1)
		panic(1, argv[1]);
}

