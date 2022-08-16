/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:23:46 by hoomen            #+#    #+#             */
/*   Updated: 2022/04/27 18:46:32 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line_bonus.h"

void	ft_init(t_struct *t)
{
	t->newstatic = NULL;
	t->line = NULL;
	t->bytesread = 1;
}

char	*ft_error(char *buffer, char *staticline)
{
	free(buffer);
	free(staticline);
	return (NULL);
}

char	*read_to_static(int fd, char *staticline, t_struct *t)
{
	char		*buffer;
	char		*newstatic;
	size_t		staticlen;
	size_t		staticlen_new;

	buffer = malloc(BUFFER_SIZE);
	if (buffer == NULL)
		return (ft_error(buffer, staticline));
	t->bytesread = read(fd, buffer, BUFFER_SIZE);
	if (t->bytesread == (size_t) -1)
		return (ft_error(buffer, staticline));
	staticlen = ft_strlen_gnl(staticline);
	staticlen_new = staticlen + t->bytesread;
	newstatic = malloc(staticlen_new + 1);
	if (newstatic == NULL)
		return (ft_error(buffer, staticline));
	ft_strncpy_gnl(newstatic, staticline, staticlen);
	ft_strncpy_gnl(newstatic + staticlen, buffer, t->bytesread);
	free(staticline);
	free(buffer);
	return (newstatic);
}

void	split_static(char *staticline, t_struct *t)
{
	size_t	rem_staticlen;
	size_t	linelen;

	linelen = ft_strlen_newline(staticline);
	if (!linelen)
		return ;
	t->line = malloc(linelen + 1); 
	if (t->line == NULL)
		return ;
	ft_strncpy_gnl(t->line, staticline, linelen);
	rem_staticlen = ft_strlen_gnl(staticline) - linelen;
	t->newstatic = malloc(rem_staticlen + 1);
	if (t->newstatic == NULL)
	{
		free(t->line);
		t->line = NULL;
		return ;
	}
	ft_strncpy_gnl(t->newstatic, staticline + linelen, rem_staticlen);
}

char	*get_next_line(int fd)
{
	static char	*staticlines[FD_MAX];
	t_struct	t;
	
	if (BUFFER_SIZE < 1 || fd < 0 || fd > FD_MAX)
		return (NULL);
	ft_init(&t);
	if (staticlines[fd] == NULL)
		staticlines[fd] = read_to_static(fd, staticlines[fd], &t);
	while (staticlines[fd] != NULL && !ft_strchr_gnl(staticlines[fd], '\n') && t.bytesread)
		staticlines[fd] = read_to_static(fd, staticlines[fd], &t);
	if (staticlines[fd] == NULL)
		return (NULL);
	split_static(staticlines[fd], &t);
	free(staticlines[fd]);
	staticlines[fd] = t.newstatic;
	return (t.line);
}

// int main(void)
// {
// 	FILE	*file;
// 	FILE	*file2;
// 	char	*line;
// 	int		fd;
// 	int		fd2;
// 	int		i;

// 	file = fopen("empty.txt", "r");
// 	file2 = fopen("text.txt", "r");
// 	fd = fileno(file);
// 	fd2 = fileno(file2);
// 	i = 0;
// 	while(i < 10)
// 	{
// 		line = get_next_line(fd);
// 		printf("line = %s", line);
// 		free(line);
// 		line = get_next_line(fd2);
// 		printf("line = %s", line);
// 		free(line);
// 		i++;
// 	}
// 	fclose(file);
// }

