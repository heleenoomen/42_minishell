/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktashbae <ktashbae@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:27:37 by ktashbae          #+#    #+#             */
/*   Updated: 2022/07/26 02:57:03 by ktashbae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "minishell.h"

#define INPUT 0
#define OUTPUT 1
#define APPEND 2

char	*ft_strtok(char *str, const char *delim)
{
	static char	*index;
	int			i;

	if (str != NULL)
		index = str;
	else
		str = index;
	if (*index == '\0')
		return (NULL);
	while (*index != '\0')
	{
		i = 0;
		while (delim[i] != '\0')
		{
			if (*index == delim[i])
			{
				if (index == str)
				{
					str++;
					index++;
				}
				else
				{
					*index = '\0';
					break ;
				}
			}
			i++;
		}
		if (*index == '\0')
		{
			index++;
			return (str);
		}
		index++;
	}
	return (str);
}

void	skip_whitespace(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[0] == ' ' || str[0] == '\n')
		ft_memmove(str, str + 1, len);
	if (str[len - 1] == ' ' || str[len - 1] == '\n')
		str[len - 1] = '\0';
}

void	tokenizer(char **node, int *type, char *input, const char *delim)
{
	char	*token;
	int		i;

	i = -1;
	token = ft_strtok(input, delim);
	while (token != NULL)
	{
		node[++i] = malloc(sizeof(token) + 1);
		ft_strcpy(node[i], token);
		skip_whitespice(node[i]);
		token = ft_strtok(NULL, delim);
	}
	node[++i] = NULL;
	*type = i;
}

void	parser(char *input)
{
	char	*node[100];
	char	*cmd[100];
	int		type;

	if (ft_strchr(input, '|'))
	{
		tokenizer(node, &type, input, "|");
		run_pipe(node, type);
	}
	else if (ft_strchr(input, '>'))
	{
		tokenizer(node, &type, input, ">");
		if (type == 2)
			run_redirect(node, type, OUTPUT);
		else
			perror("Incorrect input");
	}
	else if (ft_strchr(input, '<'))
	{
		tokenizer(node, &type, input, "<");
		if (type == 2)
			run_redirect(node, type, INPUT);
		else
			perror("Incorrect input");
	}
	else if (ft_strstr(input, ">>"))
	{
		tokenizer(node, &type, input, ">>");
		if (type == 2)
			run_redirect(node, type, APPEND);
		else
			perror("Incorrect input");
	}
	else
		run_command(cmd);
}
