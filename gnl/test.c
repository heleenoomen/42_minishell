#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

size_t	ft_strlen(char const *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_join(char *statics, char *s)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*joined;

	i = 0;
	if (statics == NULL)
	{
		joined = malloc(ft_strlen(s) + 1);
		while (s[i])
		{
			joined[i] = s[i];
			i++;
		}
		joined[i] = '\0';
		return (joined);
	}
	len = ft_strlen(statics) + ft_strlen(s);
	joined = malloc(len + 1);
	if (joined == NULL)
		return (NULL);
	while (statics[i])
	{
		joined[i] = statics[i];
		i++;
	}
	j = 0;
	while (s[i])
	{
		joined[i + j] = s[j];
		j++;
	}
	joined[i + j] = '\0';
	free (statics);
	//free (s);
	return (joined);
}

char	*ft_read(int fd, int bufsize)
{
	static char		*static;
	size_t			templen;

	s = malloc(bufsize);
	read(fd, s, bufsize);
	statics = ft_join(statics, s);
	return (s);
}

int main(void)
{
	FILE	*file;
	int		fd;
	char	*s;
	int		i;

	file = fopen("test.txt", "r");
	fd = fileno(file);
	i = 0;
	s = ft_read(fd, 4);
	printf("%s\n", s);
	free(s);
	s = ft_read(fd, 4);
	printf("%s\n", s);
	free(s);
	s = ft_read(fd, 4);
	printf("%s\n", s);
	free (s);
}