#include "../../includes/minishell.h"

int change_directory(const char *path)
{
	char current_dir[256];

	getcwd(current_dir, sizeof(current_dir));
	if (chdir(path) == -1)
	{
		perror("cd");
		return -1;
	}
	getcwd(current_dir, sizeof(current_dir));

	return 0;
}

int cd(char *str, char **matrix)
{
	if (ft_matrixlen((const char **)matrix) <= 2)
	{
		if (str == NULL)
		{
			char *home_dir = search(g_shell.hash, "HOME");
			if (home_dir == NULL)
			{
				perror("cd");
				return -1;
			}
			return change_directory(home_dir);
		}
		else
			return change_directory(str);
	}
	else
		return (ft_printf("to many args\n"));

	return 0;
}