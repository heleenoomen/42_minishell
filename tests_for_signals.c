#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	//segfault
	// char *s = NULL;

	// printf("%c\n", *s);

	//bus error
	// char *s = "hello";

	// s[1] = 'a';
	
	//endless loop
	while(1);

	//exit with status
	// exit(87);
}