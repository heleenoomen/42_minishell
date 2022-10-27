/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:46:54 by hoomen            #+#    #+#             */
/*   Updated: 2022/10/27 21:16:16 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_edge(char *arg)
{
	if (ft_strcmp(arg, "9223372036854775808") == 0)
		return (false);
	if (ft_strcmp(arg, "-9223372036854775809") == 0)
		return (false);
	if (ft_strlen(arg) > 21)
		return (false);
	return (true);
}

bool	exit_is_valid(char *arg)
{
	if (check_edge(arg) == false)
		return (false);
	while (*arg == ' ' || *arg == '\t')
		arg++;
	if (*arg == '\0')
		return (false);
	if (*arg == '-' || *arg == '+')
		arg++;
	if (!ft_isdigit(*arg))
		return (false);
	while (*arg)
	{
		if (*arg == ' ' || *arg == '\t')
			break ;
		if (!ft_isdigit(*arg))
			return (false);
		arg++;
	}
	if (*arg == '\0')
		return (true);
	while (*arg == ' ' || *arg == '\t')
		arg++;
	if (*arg == '\0')
		return (true);
	return (false);
}

static long int	calculate_number(const char *str, int i, int sign)
{
	unsigned long long	nb;

	nb = 0;
	while (ft_isdigit(str[i]))
	{
		nb = nb * 10 + ((str[i]) - '0');
		i++;
	}
	return (nb * sign);
}

long long	ft_atoll(const char *str)
{
	int			i;
	long long	nb;
	int			sign;

	if (str == NULL)
		return (0);
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	nb = calculate_number(str, i, sign);
	return (nb);
}

void	mini_exit(int argc, char **argv, t_minishell *minishell)
{
	bool	valid;

	if (argc > 1)
	{
		valid = exit_is_valid(argv[1]);
		if (valid)
			g_global_exit_status = (int)((unsigned char)ft_atoll(argv[1]));
		else
			g_global_exit_status = 255;
	}
	ft_putstr_fd("exit\n", 1);
	if (argc > 1 && !valid)
	{
		print_error("exit", argv[1], NULL, -1);
		ft_putstr_fd("numeric argument required\n", 2);
	}
	free_minishell(minishell);
	free(argv);
	reset_echoctl(&(minishell->termios_cpy));
	//system("leaks minishell");
	exit(g_global_exit_status);
}
