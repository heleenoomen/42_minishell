#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (i);
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	ft_strlencpy(char *dst, const char *src, size_t dstlen)
{
	size_t	i;

	i = 0;
	while (src[i] && i < dstlen)
	{
		dst[i] = src[i];
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	bytes;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	bytes = count * size;
	ptr = malloc(bytes);
	if (ptr == NULL)
		return ptr;
	while (bytes)
	{
		ptr[bytes] = '\0';
		bytes--;
	}
	return ((void *) ptr);
}

char	*ft_add_to_static(char *staticline, char *line)
{
	char	*newstatic;
	size_t	staticlen;
	size_t	i;

	if (staticline == NULL)
	{
		newstatic = ft_calloc(BUFFER_SIZE + 1, 1);
		if (newstatic == NULL)
			return (NULL);
		ft_strlencpy(newstatic, line, BUFFER_SIZE);
		return (newstatic);
	}
	staticlen = ft_strlen_gnl(staticline);
	newstatic = ft_calloc(staticlen + BUFFER_SIZE + 1, 1);
	if (newstatic == NULL)
		return (NULL);
	ft_strlencpy(newstatic, staticline, staticlen);
	printf("newstatic 69 = %s\n", newstatic);
	ft_strlencpy(newstatic + staticlen, line, BUFFER_SIZE);
	free(staticline);
	return(newstatic);
}

int main(void)
{
	char *staticline;
	char *line;

	staticline = ft_calloc(5, 1);
	ft_strlencpy(staticline, "boot", 4);
	printf("staticline 81 = %s\n", staticline);
	line = malloc(2);
	ft_strlencpy(line, "\nt", 2);
	staticline = ft_add_to_static(staticline, line);
	printf("staticline 85 = %s\n", staticline);
	free (staticline);
	free (line);
}