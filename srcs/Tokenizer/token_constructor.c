/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_constructor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:14:53 by adantas-          #+#    #+#             */
/*   Updated: 2023/06/27 16:14:53 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**count_and_fill(char *input, size_t *nbr_cmds)
{
	char	**commands;
	size_t	index;

	count_cmds(input, nbr_cmds);
	commands = (char **)ft_calloc((*nbr_cmds) + 1, sizeof(char *));
	index = 0;
	while (index < (*nbr_cmds))
	{
		commands[index] = extract_cmd(&input);
		index++;
	}
	commands[index] = NULL;
	return (commands);
}

void	tokenizer(char *input, t_hash *hash)
{
	char	**commands;
	size_t	nbr_cmds;

	nbr_cmds = 0;
	commands = count_and_fill(input, &nbr_cmds);
	free(input);
	if (set_up_global(commands, nbr_cmds, hash) == REDI_SIGNAL)
		g_shell.nbr_sons = 0;
	ft_free_matrix((void **)commands);
	deslocate_expansion_empty();
}
