#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*line1 = "lim";
	char	*line2 = "lim";

	dprintf(2, "%d\n", strcmp(line1, line2));
}
