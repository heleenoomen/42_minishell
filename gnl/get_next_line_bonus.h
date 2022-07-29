/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:32:47 by hoomen            #+#    #+#             */
/*   Updated: 2022/04/27 18:45:47 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include<stdio.h>
# include<stdlib.h>
# include<unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

# define FD_MAX 1024

typedef struct s_struct
{
	char	*newstatic;
	char	*line;
	size_t	bytesread;
}			t_struct;


int		ft_strchr_gnl(const char *s, char c);
size_t	ft_strlen_gnl(const char *s);
size_t	ft_strlen_newline(char *s);
void	ft_strncpy_gnl(char *dst, const char *src, size_t n);
void	ft_init(t_struct *t);
char	*ft_error(char *buffer, char *staticline);
char	*read_to_static(int fd, char *staticline, t_struct *t);
void	split_static(char *staticline, t_struct *t);
char	*get_next_line(int fd);

#endif
