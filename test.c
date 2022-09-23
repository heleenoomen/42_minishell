#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	printf("%p\n", envp);
	printf("%p\n", envp[0]);
}