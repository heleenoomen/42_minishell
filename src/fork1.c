#include "minishell.h"

//	while (1)//getcmd(buf, sizeof(buf)) >= 0)
int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork", NULL);
	return pid;
}

