#include "../../includes/minishell.h"

static char	**count_and_fill(char *input, size_t *nbr_cmds)
{
	char	**commands;
	size_t	index;

	count_cmds(input, nbr_cmds);
	commands = (char **)ft_calloc((*nbr_cmds) + 1, sizeof(char *));
	index = 0;
	while (index < (*nbr_cmds))
	{
		commands[index] = extract_cmd(&input);
		index++;
	}
	commands[index] = NULL;
	return (commands);
}

void	tokenizer(char *input, t_hash *hash)
{
	char	**commands;
	size_t	nbr_cmds;

	nbr_cmds = 0;
	commands = count_and_fill(input, &nbr_cmds);
	free(input);
	for (int i = 0; commands && *commands && commands[i]; i++){
		executor(commands[i]);
		hash_conver();
	}
	ft_free_matrix((void **)commands);
	(void)hash;

}
