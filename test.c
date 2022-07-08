#include<stdio.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<sys/wait.h>
#include"libft.h"

// int	take_input(char *s)
// {
// 	char	*buf;

// 	buf = readline("\n>>> ");
// 	if (ft_strlen(buf) != 0)
// 	{
// 		add_history(buf);
// 		ft_strlcpy(s, buf, ft_strlen(buf));
// 		return (0);
// 	}
// 	return (1);
// }

int	main(void)
{
	char	*username;
	// char	inputstring[1000];

	username = getenv("USER");
	printf("USER IS: %s\n", username);
	sleep(3);
	printf("\033[H\033[J");
	// take_input(inputstring);
	// system("leaks a.out");
	return (1);
}