#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	int	pid;

	pid = fork();
	printf("%i\n", pid);
	if (pid == 0)
		exit(0);
	wait(NULL);
	return (0);
}