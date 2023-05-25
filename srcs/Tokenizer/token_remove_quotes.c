#include "../../includes/minishell.h"

static void move_quotes(char *str, char *new, size_t *index, size_t *new_index)
{
    new[*new_index] = str[*index]; 
    (*new_index)++;  
    (*index)++; 
}

static void copy_edited_str(char *str, char *new, size_t *index, size_t *new_index)
{
	new = (char *)ft_calloc(get_edit_size(str) + 1, sizeof(char));

	while (str[*index] != '\0')
	{
		if (str[*index] == '\'' || str[*index] == '\"')
		{
			move_quotes(str, new, index, new_index);
		}
		else if (str[*index] == '$')
		{
			expand_vars(str, g_shell.hash);
		}
		else
		{
			new[*new_index] = str[*index];
			(*new_index)++;
			(*index)++;
		}
	}
}

char **remove_quotes_and_expand(char **matrix)
{
	char **new;
	char **free_me;
	size_t size = 0;

	if (*matrix == NULL)
		return matrix;

	free_me = matrix;
	new = (char **)ft_calloc(ft_matrixlen((const char **)matrix) + 1, sizeof(char *));

	while (*matrix)
	{
		new[size] = (char *)ft_calloc(ft_strlen(*matrix) + 1, sizeof(char));
		size_t index = 0;
		size_t new_index = 0;
		copy_edited_str(*matrix, new[size], &index, &new_index);
		size++;
		matrix++;
	}

	ft_free_matrix((void **)free_me);
	return new;
}
