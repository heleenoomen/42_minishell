#include "minishell.h"

//int	main(void)
//{
//	static char	*buf;
//	int		fd;
//
	//Ensure that three file descriptors are open.
//	while ((fd = open("console", O_RDWR)) >= 0) 
//	{
//		if (fd >= 3)
//		{
//			close (fd);
//			break;
//		}
//	}
	//Read and run input commands.
//	while (1)//getcmd(buf, sizeof(buf)) >= 0)
//	{
//		buf = readline("Minishell>>> ");
//		if (buf == NULL)
//			break ;
//		else
//		{
//			if (fork1() == 0)
//				runcmd(parsecmd(buf));
//			wait(0);
//			add_history(buf);
//			free(buf);
//		}
//	}
//	clear_history();
//	return (0);
//}


//		if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
			// Chdir must be called by the parent, not the child.
//		{
//			buf[strlen(buf) - 1] = 0; //chop \n
//			if (chdir(buf + 3) < 0)
//				dprintf(2, "cannot cd %s\n", buf+3);
//			continue;
//		}
//		if (fork1() == 0)
//			runcmd(parsecmd(buf));
//		wait(0);
//	}
//	exit(0);
//}
	
void	panic(char *s)
{
	dprintf(2, "%s\n", s);
	exit(1);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		panic("fork");
	return pid;
}

