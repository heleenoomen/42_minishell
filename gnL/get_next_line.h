/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:47:44 by ktashbae          #+#    #+#             */
/*   Updated: 2022/09/22 16:52:45 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>

char	*ft_strjoin_gnL(char *s1, char *s2);
char	*ft_strchr_gnL(char *s, int c);
char	*ft_strdup_gnL(char *src);
char	*get_next_line(int fd);

#endif
