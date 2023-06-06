#include "../../includes/minishell.h"

/* static int syntax_error(char *str)
{
	if (!(*str == '_' || isalpha(*str)))
		return (-1);
	while (*++str)
	if (!isalnum(*str) && *str != '_')
		return (-1);
	return (1);
}

static char	*extract_variable(char *str)
{
	int i = 0;
	printf("varible = %s\n", str);
	while (str[i] && str[i] != '=')
		i++;
	str[i] = '\0';
	return (str);
}

static char	*extract_value(char *str)
{
	while (*str && *str != '=' && !(*str >= ' ' && *str <= '\t'))
		str++;
	return (str + 1);
}

void	export(char *str, t_hash *hash)
{
	char	*existing_value;
	char	*variable;
	char	*value;

	while (*str && (*str != ' ' && *str != '\t'))
		str++;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;

	variable = ft_strdup(extract_variable(str));
	if (syntax_error(variable) != 1)
		return ((void)printf("[export:`%s`:not a valid identifier]\n", str));

	value = extract_value(str);
	existing_value = search(hash, variable);
	if (existing_value == NULL)
		insert_node(hash, variable, value);
	else
		insert_node(hash, variable, value);
	printf("Exported %s=%s\n", variable, value);
} */

static void	print_vars(void)
{
	t_node	*node;
	size_t	looper;

	looper = 0;
	while (looper < HASH_SIZE)
	{
		node = g_shell.hash->list[looper];
		while (node != NULL)
		{
			if (node->value != NULL)
				ft_printf_ln(EXPORT_PRINT_VALUE, node->key, node->value);
			else
				ft_printf_ln(EXPORT_PRINT_VAR, node->key);
			node = node->next;
		}
		looper++;
	}
	free_son();
	exit(EXIT_SUCCESS);
}

static int	fake_add_var(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (FALSE);
	while (ft_isalnum(*arg) || *arg == '_')
		arg++;
	if (*arg != '=' && *arg != '\0')
		return (FALSE);
	return (TRUE);
}

static void	add_new_vars(char **argv)
{
	argv++;
	while (*argv != NULL)
	{
		if (fake_add_var(*argv) == FALSE)
		{
			ft_printf_fd(STDERR_FILENO, ERR_EXPORT_INVALID, *argv);
			free_son();
			exit(EXIT_FAILURE);
		}
		argv++;
	}
}

void	ft_export(char **argv)
{
	if (*(argv + 1) == NULL || **(argv + 1) == '\0')
		print_vars();
	add_new_vars(argv);
	free_son();
	exit(EXIT_SUCCESS);
}
