#include "../includes/minishell.h"

void	buitins(char **commands)
{
	if (ft_strcmp(commands[0], "echo") == 0)
		echo(commands);
	else if (ft_strcmp(commands[0], "cd") == 0)
		cd(commands[1], commands);
	else if (ft_strcmp(commands[0], "env") == 0)
		ft_printf("printf ENVP");
}