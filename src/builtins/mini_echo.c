/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:53:53 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/10 17:06:51 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* checks if argv[1] is -n option. if so, sets the value at i to 2. Checks for
 * and moves through any subsequent arguments equal to the string "-n", which
 * will not be printed and have no effect. If the first element after the last
 * "-n" argument is not NULL, newline is set to zero (i.e. mini_echo will not 
 * print a newline). If the first argument after the last "-n" argument is
 * NULL, newline is set to 1 (i.e. a newline will be printed if echo is called
 * without any arguments (=with only "-n" options)
 */
void	set_newline(char **argv, bool *newline, int *i)
{
	if (ft_strncmp(argv[1], "-n", 3) == 0)
	{
		*i = 2;
		while (argv[*i] != NULL && ft_strncmp(argv[*i], "-n", 3) == 0)
			(*i)++;
		if (argv[*i] == NULL)
			*newline = 1;
		else
			*newline = 0;
	}
	else
	{
		*newline = 1;
		*i = 1;
	}
}

/* checks if echo is called without any arguments, in that case, prints a
 * newline and returns. Calls set_newline to set the newline value (1 in 
 * case a newline should be printed, zero in case no newline should be
 * printed). Cycles through all further arguments and prints them, separated
 * by spaces. Prints a newline after last arguments if newline was set
 * to 1.
 */
void	mini_echo(int argc, char **argv)
{
	bool	newline;
	int		i;

	if (argc == 1)
	{
		write (1, "\n", 1);
		return ;
	}
	set_newline(argv, &newline, &i);
	while (argv[i + 1] != NULL)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		write(1, " ", 1);
		i++;
	}
	write(1, argv[i], ft_strlen(argv[i]));
	if (newline)
		write(1, "\n", 1);
}

