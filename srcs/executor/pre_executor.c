/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_executor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:16:20 by adantas-          #+#    #+#             */
/*   Updated: 2023/07/14 21:59:19 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_on_error(size_t looper)
{
	while (looper < g_shell.id)
	{
		ft_free_matrix((void **)g_shell.command[looper].argv);
		if (g_shell.command[looper].wr_here > STDOUT_FILENO)
			close(g_shell.command[looper].wr_here);
		if (g_shell.command[looper].rd_here > STDIN_FILENO)
			close(g_shell.command[looper].rd_here);
		looper++;
	}
	ft_free_matrix((void **)g_shell.command[looper].argv);
}

static void	free_father_global(int has_error)
{
	size_t	looper;

	looper = 0;
	if (has_error == TRUE)
	{
		free_on_error(looper);
		return ;
	}
	while (looper < g_shell.nbr_sons)
	{
		ft_free_matrix((void **)g_shell.command[looper].argv);
		if (g_shell.command[looper].wr_here > STDOUT_FILENO)
			close(g_shell.command[looper].wr_here);
		if (g_shell.command[looper].rd_here > STDIN_FILENO)
			close(g_shell.command[looper].rd_here);
		looper++;
	}
}

void	pre_executor(void)
{
	if (g_shell.nbr_sons == 1 && g_shell.command->argv != NULL && \
	isbuiltin(g_shell.command->argv[0]) == TRUE)
	{
		father_execute(g_shell.command[0].argv);
		free_father_global(FALSE);
	}
	else if (g_shell.nbr_sons > 0)
	{
		executor();
		free_father_global(FALSE);
	}
	else if (g_shell.nbr_sons == 0)
	{
		free_father_global(TRUE);
		insert_node(g_shell.hash, STATUS_CODE, HEREDOC_CONTROL_C);
	}
	else
	{
		free_father_global(TRUE);
		insert_node(g_shell.hash, STATUS_CODE, FATHER_FAILURE);
	}
	ft_free_matrix((void **)g_shell.envp);
	free(g_shell.command);
}
