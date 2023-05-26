#include "../../includes/minishell.h"

char **matrix_creator()
{
	char **matrix;

	matrix = (char **)malloc(sizeof(char *) * HASH_SIZE);

	return (matrix);
}

static void node_view(t_node *node)
{
	while (node && node->next)
	{
		if (node)
			ft_printf("%s=%s\n",node->key, node->value);

		node = node->next;
	}
	
}

void	hash_conver()
{
		t_hash *hash;
		int	i;
		//int	j;

		//j = 0;
		i = 0;
		hash = g_shell.hash;
		
		while (i <= HASH_SIZE)
		{
			if (hash->list[i])
			{
				node_view(hash->list[i]);

			}
			i++;
		}
}