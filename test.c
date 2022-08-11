#include <string.h>
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	char *name = ttyname(0);

	printf("%s\n", name);
}
