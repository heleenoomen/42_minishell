# include "minishell.h"

int	builtin_echo(int argc, char **argv, t_env *env)
{
	if (argc == 1)
		return (0);
	
