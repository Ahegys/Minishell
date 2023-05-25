#include "../includes/minishell.h"

static char **bins_paths()
{
	char **bins_path;

	bins_path = ft_split(search(g_shell.hash, "PATH"), ':');
	return (bins_path);
}

static char **add_bar_to_execute()
{
	char **bin;
	char *path;
	int i = 0;

	bin = bins_paths();

	while (bin && *bin && bin[i])
	{
		if (!(bin[i][ft_strlen(bin[i]) - 1] == '/'))
		{
			path = ft_strjoin(bin[i], "/");
			free(bin[i]);
			bin[i] = path;
		}
		i++;
	}

	return (bin);
}

static char **create_path_executable(char *command)
{
	char **bin;
	int i;
	char *path;
	i = 0;
	bin = add_bar_to_execute();

	while (bin && *bin && bin[i])
	{
		path = ft_strjoin(bin[i], command);
		free(bin[i]);
		bin[i] = path;
		i++;
	}
	bin[i] = NULL;
	return (bin);
}

static void runtime(char **bins, char **args)
{
	pid_t	pid;
	int		executed;
	int		i;
	executed = 0;
	i = 0;

	while (bins && *bins && bins[i])
	{
		if (access(bins[i], X_OK) == 0 && !executed)
		{
			executed = 1;
			pid = fork();
			if (pid == 0)
			{
				if (execve(bins[i], args, g_shell.envp) == -1)
					perror("execvp");
				exit(0);
			}
			else if (pid > 0)
				wait(NULL);
			else
				perror("fork");
		}
		i++;
	}
	ft_free_matrix((void **)bins);
}

void executor(char *line)
{
	char **args;

	args = ft_split(line, -7);
	if (isbuiltin(args[0]))
		buitins(args);
	else
	{
		runtime(create_path_executable(args[0]), args);
		ft_free_matrix((void **)args);
	}
}