/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:18:15 by adantas-          #+#    #+#             */
/*   Updated: 2023/06/27 16:18:43 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*expand_vars_heredoc(char *str, t_hash *hash)
{
	char	*expanded_str;
	size_t	size;

	if (ft_strchr(str, '$'))
	{
		size = size_with_values_heredoc(str, hash);
		expanded_str = (char *)ft_calloc((size + 1), sizeof(char));
		copy_with_expansions_heredoc(str, expanded_str, hash);
		return (expanded_str);
	}
	else
		return (str);
}

static char	*heredoc_expand(char *str)
{
	char	*new;

	new = expand_vars_heredoc(str, g_shell.hash);
	if (str == new)
		return (str);
	free(str);
	return (new);
}

void	expansion_loop(char *limiter, t_command *son, size_t id)
{
	char	*line;

	while (TRUE)
	{
		line = readline(HEREDOC_PROMPT);
		if (line == NULL)
		{
			ft_printf_fd(STDERR_FILENO, WAR_HEREDOC, limiter);
			break ;
		}
		else if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		else if (*line != '\0')
			line = heredoc_expand(line);
		ft_putendl_fd(line, son[id].rd_here);
		free(line);
	}
}

void	no_expansion_loop(char *limiter, t_command *son, size_t id)
{
	char	*line;

	while (TRUE)
	{
		line = readline(HEREDOC_PROMPT);
		if (line == NULL)
		{
			ft_printf_fd(STDERR_FILENO, WAR_HEREDOC, limiter);
			break ;
		}
		else if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, son[id].rd_here);
		free(line);
	}
}
