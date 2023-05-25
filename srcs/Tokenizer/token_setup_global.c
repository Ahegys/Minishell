#include "../../includes/minishell.h"

static char **hash_to_matrix(t_pipe *hash){
	(void)hash;
	return (NULL);
}

int set_up_global(char **cmds, size_t nbr_cmds, t_pipe *hash)
{
	int status;

	g_shell.command = (t_command *)ft_calloc(nbr_cmds + 1, sizeof(t_command));
	g_shell.id = 0;
	g_shell.nbr_sons = nbr_cmds;


	while (g_shell.id < nbr_cmds)
	{
		status = fill_son_orders(&g_shell.command[g_shell.id], *cmds, hash->hash);
		if (status == REDI_SIGNAL)
			return (REDI_SIGNAL);
		g_shell.id++;
		cmds++;
	}

	g_shell.id = 0;
	g_shell.envp = hash_to_matrix(hash);

	return 0;
}
