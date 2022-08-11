#include "minishell.h"

char	*make_path(char *s, t_env *env)
{
	char	**paths;
	char	*path_plus_slash;
	char	*full_path;
	int	i;

	i = 0;
	if (access(s, F_OK) == 0)
		return (s);
	paths = NULL;
	while (i < env->size)
	{
		if (ft_strcmp("PATH", env->arr_pairs[i].key) == 0)
		{
			paths = ft_split(env->arr_pairs[i].value, ':');
			if (paths == NULL)
				panic_builtins("System error", env);
			break ;
		}
		i++;
	}
	if (paths == NULL)
		panic_builtins("Path variable not set", env);
	i = 0;
	while (paths[i] != NULL)
	{
		path_plus_slash = ft_strjoin(paths[i], "/"); 
		full_path = ft_strjoin(path_plus_slash, s);
		if (access(full_path, F_OK) == 0)
		{
			free(path_plus_slash);
			i = 0;
			while (paths[i] != NULL)
			{
				free(paths[i]);
				i++;
			}
			free(paths);
			return (full_path);
		}
		free(path_plus_slash);
		free(full_path);
		i++;
	}
	panic_builtins(s, env);
	return (NULL);
}





