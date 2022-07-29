/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 17:00:35 by hoomen            #+#    #+#             */
/*   Updated: 2022/07/20 17:30:09 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

typedef struct s_char_buf
{
	char	*char_buf;
	int		size;
	int		free;
}			t_char_buf;

# define NO_QUOTES 0
# define SINGLE_QUOTES 1
# define DOUBLE_QUOTES 2

void	free_argv_dup(char ***argv_dup);

# define ENDOFVAR "\'\" $"

/*init_char_buff
 * allocates 128 chars in buffer
 * sets size to 0
 * sets free to 128
 * error checking in calling function: if buffer.char_buf == NULL
 */
void		init_char_buf(t_char_buf *charbuf);

/*frees an array of char pointers and sets the pointer to the
 * array to NULL*/
void		free_argv_dup(char ***argv_dup);

/*expands dollar signs and removes quotes. Returns the cleaned up
 * argv as a malloced element*/
char		**expander(char **argv, t_env *env);

/* checks for unclosed quotes. Returns 0 if all quotes are closed
 * properly, returns 1 in case of unclosed quotes */
int		unclosed_quotes(char *s);

/* changes quote modus, passed by addres. The type of quotes found are paseed as an integer (SINGLE_QUOTES or DOUBLE_QUOTES)*/
int		change_quote_modus(int *in_quotes, int quote_found);

#endif
