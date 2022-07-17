/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 12:52:44 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/16 13:18:27 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		return ;
	else if (argv[1][0] == '-' && argv[1][1] == 'n')
	{
		i = 2;
		while (argv[i + 1] != NULL)	
		{
			printf("%s\n", argv[i]);
			printf(" ");
			i++;
		}
		return ;
	}
	i = 1;
	while (argv[i + 1] != NULL)
	{
		printf("%s\n", argv[i];	
		printf(" ");
		i++;
	}
}

