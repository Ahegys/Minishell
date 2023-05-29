#include "../../includes/minishell.h"

void	echo(char **command)
{
	int	i;

	if (command[1] == NULL)
	{
		ft_printf("\n");
		return;
	}
	else if (ft_strcmp(command[1], "-n") == 0)
	{
		i = 2;
		while (command && command[i])
		{
			ft_printf("%s ", command[i]);
			i++;
		}
		return;
	}
	i = 1;
	while (command && command[i])
	{
		ft_printf("%s ", command[i]);
		i++;
	}
	
	ft_putchar('\n');

}