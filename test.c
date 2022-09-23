#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	printf("%i\n", access("environment", X_OK));
}