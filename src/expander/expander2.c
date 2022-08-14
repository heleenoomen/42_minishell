/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoomen <hoomen@student.42heilbronn.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 13:21:57 by hoomen            #+#    #+#             */
/*   Updated: 2022/08/14 14:00:01 by hoomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}

/* expands a single string. Expands dollar sign, expands tilde if tilde_exp is set
 * and removes quotes if quote_removal is set.
 */
char	*expand_string(t_env *env, char *ptr, bool tilde_exp, bool quote_removal)
{
	t_char_buf	buf;
	char		*ret;

	init_char_buf(&buf);
	if (buf == NULL)
		return (NULL);
	expand_dollarsign(env, ptr, buf);
	if (buf.buf != NULL && tilde_exp)
		expand_tilde(env, ptr, buf);
	if (buf.buf != NULL && quote_removal)
		remove_quotes(env, ptr, buf);
	ret = ft_strdup(buf.buf);
	free(buf.buf);
	return (ret);
}

/* expands argv. Expands dollar signs. Expands tilde if tilde_exp is set,
 * removes quotes if quote_removal is set. Returns the expanded argv.
 * Returns NULL if argv was NULL in the first place or if malloc fails somewhere
 * along the way.
 */
char	**expander(char **argv, t_env *env, bool tilde_exp, bool quote_removal)
{
	char	**argv_dup;
	int		i;

	if (argv == NULL)
		return (NULL);
	argv_dup = ft_calloc((ft_argc(argv) + 1), sizeof(char *));
	if (argv_dup == NULL)
		return (NULL);
	i = 0;
	while (argv[i] != NULL)
	{
		argv_dup[i] = expand_string(argv[i], env, tilde_exp, quote_removal);
		if (argv_dup[i] == NULL)
		{
			ft_freestrarr(&argv_dup);
			write(2, "System error\n");
			return (NULL);
		}
		i++;
	}
	return (argv_dup);
}

