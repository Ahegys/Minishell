#include "../../includes/minishell.h"

void	echo(char **command)
{
	int	i;

	if (command[1] == NULL)
		
		return ((void)ft_printf("\n"));
	else if (ft_strcmp(command[1], "-n") == 0)
	{
		i = 2;
		while (command && command[i])
			ft_printf("%s ", command[i++]);
		return;
	}
	i = 1;
	while (command && command[i])
		ft_printf("%s ", command[i++]);

	ft_putchar('\n');
}