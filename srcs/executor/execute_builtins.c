#include "../includes/minishell.h"

void	buitins(char **commands)
{
	if (ft_strcmp(commands[0], "echo") == 0)
		ft_printf("%s\n", commands[2]);
	else if (ft_strcmp(commands[0], "cd") == 0)
		ft_printf("%s\n", commands[1]);
	else if (ft_strcmp(commands[0], "env") == 0)
		ft_printf("printf ENVP");
}