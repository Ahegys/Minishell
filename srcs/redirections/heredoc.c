#include "../../includes/minishell.h"

static void	free_son_and_exit(void)
{
	ft_free_matrix((void **)g_shell.LEXER_REST);
	ft_free_matrix((void **)g_shell.REDIRECT_REST);
	free_hash(g_shell.hash);
	while (g_shell.id > 0)
	{
		if (g_shell.command[g_shell.id].argv != NULL)
			ft_free_matrix((void **)g_shell.command[g_shell.id].argv);
		free(g_shell.command[g_shell.id].argv);
		g_shell.id--;
	}
	exit(REDI_OK);
}

static void	remove_quotes(char *limiter)
{
	while (*limiter)
	{
		if (*limiter == '\'' || *limiter == '\"')
		{
			ft_memmove(limiter, limiter + 1, ft_strlen(limiter));
			while (*limiter != '\'' && *limiter != '\"' && *limiter)
				limiter++;
			ft_memmove(limiter, limiter + 1, ft_strlen(limiter));
		}
		else
			limiter++;
	}
}


static int	without_expansions(char *limiter, t_command *son)
{
	int		pid;
	int		status;
	//char	*line;

	pid = fork();
	if (pid == 0)
	{
		heredoc_signals();
		no_expansion_loop(limiter, son);
		free_son_and_exit();
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(son->rd_here);
		unlink(HEREDOC_FILE);
		return (REDI_SIGNAL);
	}
	return (REDI_OK);
}


//static int	with_expansions

int	heredoc(char *limiter, t_command *son)
{
	son->rd_here = open(HEREDOC_FILE, O_RDWR | O_CREAT | O_TRUNC, PERM_CREATE);
	if (*limiter == '\"' || *limiter == '\'')
	{
		remove_quotes(limiter);
		return (without_expansions(limiter, son));
	}
	return (without_expansions(limiter, son));
}
