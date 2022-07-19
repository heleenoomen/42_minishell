/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:00:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/19 18:13:50 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_char_buf
{
	char	*char_buf;
	int		size;
	int		free;
}

# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTE 2

# define FIRST_CHAR_KEY "\"\'_$"

# define MEM_ERROR 1
# define INVALID_INPUT 2

#endif
