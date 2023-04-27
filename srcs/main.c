#include "../includes/minishell.h"

char	*env_collect(char *str)
{	
	int		i;
	char	*s;

	i = 0;
	s = str;
	while (s[i] != '=' && s[i])
		i++;
	s[i] = '\0';
	return (s);
}

void	printer(char *search, char **input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_strcmp(search, input[i]) == 0)
		{
			printf("%s", input[i]);
			return ;
		}
		printf("%s", input[i]);
		i++;
	}
}


void	command(char *(*read)(const char *), char **env, t_hash *hash)
{
	int		i;
	char	*input;
	char	*token;

	i = 0;
	while (env[i])
	{
		token = env_collect(env[i]);
		insert_node(hash, token, &env[i][ft_strlen(env[i]) + 1]);
		i++;
	}
	input = read("minishell:> ");
	builtins(input, hash);
}

int	main(int argc, char **argv, char **envp)
{
	t_hash	*hash;

	(void)argc;
	(void)argv;
	hash = (t_hash *)malloc(sizeof(t_hash));
	while (true)
		command(readline, envp, hash);
	return (0);
}
