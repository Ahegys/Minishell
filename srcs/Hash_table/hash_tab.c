/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adantas- <adantas-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:36:54 by adantas-          #+#    #+#             */
/*   Updated: 2023/07/07 16:37:29 by adantas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

unsigned int	hash_code(char *key)
{
	unsigned long	hash;
	unsigned int	c;

	hash = MAGIC_NUMBER;
	while (*key)
	{
		c = *key;
		hash = ((hash << 5) + hash) + c;
		key++;
	}
	return (hash % HASH_SIZE);
}

t_node	*create_node(char *key, char *value)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	insert_node(t_hash *hash, char *key, char *value)
{
	unsigned const int	index = hash_code(key);
	t_node				*node;

	node = hash->list[index];
	if (node == NULL)
		hash->list[index] = create_node(key, value);
	else
	{
		while (node)
		{
			if (ft_strcmp(node->key, key) == 0)
			{
				free(node->value);
				node->value = ft_strdup(value);
				return ;
			}
			if (node->next == NULL)
				break ;
			node = node->next;
		}
		node->next = create_node(key, value);
	}
}

char	*search(t_hash *hash, char *key)
{
	unsigned const int	index = hash_code(key);
	t_node				*node;

	node = hash->list[index];
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}
