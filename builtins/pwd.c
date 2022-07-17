/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 12:19:13 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/17 12:30:43 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishel.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

void	pwd(void)
{
	char	*working_dir;
	char	buf[4096];
	
	working_dir = getcwd(buf, 4096);
	if (working_dir == NULL)
	{
		perror(NULL);
		exit(errno);
	}
	write(1, working_dir, ft_strlen(working_dir));
	write(1, "\n", 1);
}

int	main(void)
{
	pwd();
	return(0);
}
