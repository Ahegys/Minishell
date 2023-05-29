#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "./minishell_typedefs.h"
# include "../libs/libft/includes/libft.h"


#ifdef __APPLE__
		#define SYSTEM_TYPE " \033[0;35m\033[0m "
#elif defined(_WIN32)
		#define SYSTEM_TYPE " \033[0;32m\033[0m "
#elif defined(__linux__)
		#define SYSTEM_TYPE " \033[0;36m\033[0m "
#else
		#define SYSTEM_TYPE " \033[0;31m\033[0m "
#endif

# define PROMPT "\n\033[1;34m  Minishell\033[0m\n" SYSTEM_TYPE "\033[1;33m\033[0m "
# define ERR_FORK "\e[5;31mms: forking error\e[0m"
# define ERR_QUOTE "\e[5;31mms: close this quote \e[1m`%c`\n\e[0m"
# define ERR_READING "\e[5;31mms: read error\e[0m"
# define ERR_WRITING "\e[5;31mms: write error\e[0m"
# define WAR_HEREDOC "\e[1;33mheredoc: finish with EOF, expected `%s`\e[0m"
# define PERM_CREATE 0644
# define HEREDOC_FILE "/tmp/.heredoc"
# define HEREDOC_PROMPT "here-document> "
# define ERR_UNS_SYNTAX "\e[5;31mms: unsuported syntax \e[1m`%s`\n\e[0m"
# define ERR_EOL_SYNTAX "\e[5;31mms: syntax error \e[1m`EOL`\e[0m"
# define ERR_NOW_SYNTAX "\e[5;31mms: syntax error \e[1m`%s`\n\e[0m"
# define ERR_NEXT_SYNTAX "\e[5;31mms: syntax error after \e[1m`%s`\n\e[0m"

# define REDI_OK 0
# define REDI_ERR 1
# define REDI_SIGNAL -1

# define SIGNAL_INT 130

// ! GLOBAL: NEVER DIRECTELY INCREMENT ANY POINTER INSIDE THE STRUCT;
extern t_pipe	g_shell;

// int return
int		pipe_case(char **splited_pline);
int		parser(char *str, t_hash *hash);
int		write_to_case(char **splited_pline);
int		intersections(char *str, char inter);
int		read_from_case(char **splited_pline);
int		redirection(char **str, t_command *son);
int		unclosed_quotes_case(char **pipeline, char quote);

//void return
void	hash_convert();
void	env(t_hash *hash);
void	set_up_signals(void);
void	executor(char *line);
void	echo(char **command);
void	heredoc_signals(void);
void	free_hash(t_hash *hash);
void	buitins(char **commands);
void	easter_eggs(char *flags);
void	easy_splitter(char *str);
void	pwd(char *str, t_hash *hash);
void	unset(char *str, t_hash *hash);
void	add_to_history(char *pipeline);
void	export(char *str, t_hash *hash);
void	free_all_and_exit(t_hash *hash);
void	builtins(char *input, t_hash *hash);
void	tokenizer(char *input, t_hash *hash);
void	execute_line(char *line, t_hash *hash);
void	count_cmds(char *input, size_t *n_cmds);
void	no_expansion_loop(char *limiter, t_command *son);
void	insert_node(t_hash *hash, char *key, char *value);
void	inside_quote_copy(char **str, char **new, char quote);
void	copy_with_expansions(char *str, char *new, t_hash *hash);
void	inside_quote_counter(char **str, size_t *counter, char quote);

// char retunr
char	*separator(char *str);
char	*extract_cmd(char **input);
char	*search(t_hash *hash, char *key);
char	*expand_vars(char *str, t_hash *hash);
// t_node return
t_node	*create_node(char *key, char *value);

// char ** return
char	**remove_quotes_and_expand(char **matrix);

// new functions, analyze they before putting in the right place
int		cd(char *str, char **matrix);
int		isbuiltin(char *check);
int		heredoc(char *limiter, t_command *son);
int		reading_invalid(char *file, t_hash *hash);
int		writing_invalid(char *file, t_hash *hash);
int		redirect_input(char *filename, t_command *son);
int		redirect_invalid(char **split_pline, t_hash *hash);
int		redirect_output_trunc(char *filename, t_command *son);
int		redirect_output_append(char *filename, t_command *son);
int		fill_son_orders(t_command *son_struct, char *cmd, t_hash *hash);
size_t	get_edit_size(char *str);
// pid_t return
pid_t	execute_command(char **args, t_hash *hash);

#endif // minishell.h
