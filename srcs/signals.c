#include "../includes/minishell.h"

static void	re_print_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	exit_heredoc(int sig)
{
	ft_putchar('\n');
	ft_free_matrix((void **)g_shell.pipeline_rest);
	ft_free_matrix((void **)g_shell.redirect_rest);
	while (g_shell.id < g_shell.nbr_sons)
	{
		if (*g_shell.command[g_shell.id].argv != NULL)
			ft_free_matrix((void **)g_shell.command[g_shell.id].argv);
		if (g_shell.command[g_shell.id].wr_here > STDOUT_FILENO)
			close(g_shell.command[g_shell.id].wr_here);
		if (g_shell.command[g_shell.id].rd_here > STDIN_FILENO)
			close(g_shell.command[g_shell.id].rd_here);
		g_shell.id--;
	}
	free_hash(g_shell.hash);
	if (sig == SIGINT)
	{
		printf("VC DEU CTRLC NO HEREDOC\n"); // remover depois
		exit(130);
	}
	exit(REDI_OK);
}

void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	heredoc_signals(void)
{
	signal(SIGINT, exit_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	set_up_signals(void)
{
	signal(SIGINT, re_print_prompt);
	signal(SIGQUIT, SIG_IGN);
}
