#include "../../includes/minishell.h"

int redirect_output_trunc(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, PERM_CREATE);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}


int redirect_output_append(char *filename)
{
	int fd;


	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, PERM_CREATE);
	if (fd == -1)
		return (-1);


	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}

	close(fd);
	return (0);
}

int redirect_input(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);

	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (-1);
	}

	close(fd);
	return (0);
}

int redirect_input_string(char *str)
{
	int pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);

	if (write(pipefd[1], str, ft_strlen(str)) == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		return (-1);
	}
	close(pipefd[1]);

	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		return (-1);
	}
	close(pipefd[0]);
	return (0);
}

int		redirection(char *str, t_hash *hash)
{
	int			i;
	int			original_stdout;
	char		**tokens;
	t_redirect	this;


	i = 0;
	tokens = ft_split(str, -7);
	original_stdout = dup(STDOUT_FILENO);
	while (tokens && *tokens && tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0)
		{
			if (tokens[i + 1])
				redirect_output_trunc(tokens[i + 1]);
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
		{
			if (tokens[i + 1])
				redirect_output_append(tokens[i + 1]);
		}
		else if (ft_strcmp(tokens[i], "<<") == 0)
		{
			if (tokens[i + 1])
			{
				this.delimiter = tokens[i + 1];
				heredoc(hash, &this);
			}
		}
		i++;
	}
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdout);
	return (1);
}
