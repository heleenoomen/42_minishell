#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

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

int main(void)
{
	FILE	*file;
	int		fd;
	char	*buffer;
	char	*s;
	int		buffersize;
	
	file = fopen("test.txt", "r");
	fd = fileno(file);
	buffersize = 3;
	buffer = malloc(buffersize);
	read(fd, buffer, buffersize);
	s = ft_calloc(buffersize + 1, 1);
	ft_strlencpy(s, buffer, buffersize);
	printf("%c%c%c\n", buffer[0], buffer[1], buffer[2]);
	free(s);
	fclose(file);
}