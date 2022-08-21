/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 10:19:31 by ktashbae          #+#    #+#             */
/*   Updated: 2022/08/16 16:18:30 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/* checks for assignment operator and type of character, returns
flag as false if assignment and alphanumeric type is found*/
int	check_value_assign(char *str)
{
	int	i;
	int	flag;

	if (str == NULL)
		return (0);
	i = 1;
	flag = 1;
	if (str[0] != '_' && ft_isalpha(str[0]) == 0)
		flag = 0;
	while (flag == 1 && str[i])
	{
		if (str[0] != '_' && ft_isalnum(str[i]) == 0)
			flag = 0;
		i++;
	}
	return (flag);
}

/* increases the size of the buffer from current into 
updated size
*/
char	*increase_buffer(void *temp1, int current_size, int update_size)
{
	void	*temp2;

	temp2 = NULL;
	if (current_size < update_size)
	{
		temp2 = malloc(update_size);
		if (temp2 == NULL)
			return (NULL);
		if (temp1 != NULL)
		{
			ft_memcpy(temp2, temp1, current_size);
			free(temp1);
		}
	}
	else
		temp2 = temp1;
	return (temp2);
}

/* saves incoming character into string pointer of lexer
according to index position. In case, the length of lexer 
reaches the limit, increase buffer reallocates size by 2*/
void	save_buffer(t_lexer *lex, char c)
{
	void	*temp;

	temp = NULL;
	lex->tokens[lex->index++] = c;
	if (lex->index >= lex->len)
	{
		temp = increase_buffer(temp, lex->len, lex->len * 2);
		if (temp == NULL)
			return ;
		lex->len *= 2;
		lex->tokens = (char *)temp;
	}
}

/* skips whitespace, if operator symbol is found - calls another function,
else saves the character to the buffer of lexer. Returns True if
character was found and saved properly, else False */
int	update_buffer(t_lexer *lex, t_prompt *line, char c)
{
	int	found;

	found = 0;
	if (c == ' ' || c == '\t')
	{
		if (lex->index > 0)
			found = 1;
	}
	else if (c == '&' || c == '(' || c == ')' || \
		|| c == '|' || c == '>' || c == '<' || c == '\n')
	{
		token_operator(lex, line, c);
		found = 1;
	}
	else
		save_buffer(lex, c);
	return (found);
}