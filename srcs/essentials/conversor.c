#include "../../includes/minishell.h"

char **matrix_creator()
{
	char	**matrix;
	int		i;

	i = 0;
	matrix = (char **)ft_calloc(sizeof(char *),HASH_SIZE);
	while (i < HASH_SIZE)
	{
		matrix[i] = NULL;
		i++;
	}

	return (matrix);
}

static char *construct_env(t_node *node)
{
	char *str;

	if (node)
	{
		str = ft_strjoin(node->key, "=");
		str = ft_strjoin(str, node->value);
		return (str);
	}

	return (NULL);
}

static void	make_envp(t_node *next, t_env *env)
{
	char	*str;

	while (next)
	{
		if (next)
		{
			str = construct_env(next);
			env->env[env->size] = ft_strdup(str);
			env->size++;
		}
		next = next->next;
	}
}

void hash_convert()
{
	t_hash *hash;
	int		i = 0;
	t_env	env;

	env.size = 0;
	env.env = matrix_creator();
	hash = g_shell.hash;
	while (i < HASH_SIZE) {
		if (hash->list[i] != NULL)
			make_envp(hash->list[i], &env);
		i++;
	}
	g_shell.env_m = env.env;
}