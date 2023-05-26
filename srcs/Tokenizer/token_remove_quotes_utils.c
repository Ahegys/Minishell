#include "../../includes/minishell.h"

static void value_size(char *str, size_t *index, size_t *counter)
{
		size_t var_len = 0;
		(*index)++;
		if (!(str[*index] >= '0' && str[*index] <= '9'))
		{
				if (str[*index] == '?')
				{
						const char *value = search(g_shell.hash, "?");
						(*counter) += strlen(value);
						(*index)++;
						while ((ft_isalpha(str[*index]) || str[*index] == '_') && str[*index] != '\0')
								(*index)++;
				}
				else
				{
						while (str[*index] != '\0')
						{
								var_len++;
								(*index)++;
						}
						(*counter) += var_len;
				}
		}
		else
		{
				while (str[*index] >= '0' && str[*index] <= '9')
				{
						var_len = var_len * 10 + (str[*index] - '0');
						(*index)++;
				}
				(*counter) += var_len;
		}
}
static void count_quotes(char *str, size_t *index, size_t *counter, char ref)
{
	(*index)++;
	(*counter)++;
	if (ref == '\'')
		while (str[*index] != ref)
		{
			(*counter)++;
			(*index)++;
		}
	else
	{
		while (str[*index] != ref)
		{
			if (str[*index] == '$')
				value_size(str, index, counter);
			else
			{
				(*counter)++;
				(*index)++;
			}
		}
	}
}

size_t	get_edit_size(char *str)
{
	size_t	index;
	size_t	counter;

	index = 0;
	counter = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\'' || str[index] == '\"')
			count_quotes(str, &index, &counter, str[index]);
		else if (str[index] == '$')
			value_size(str, &index, &counter);
		else
		{
			counter++;
			index++;
		}
	}
	return (counter);
}
