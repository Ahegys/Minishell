#============ [FILES] ==========
NAME = minishell

FILES = main.c \
		easter_eggs.c \
		signals.c \
		builtins.c \
		cd.c \
		echo.c \
		echo_utils.c \
		env.c \
		exit.c \
		export.c \
		pwd.c \
		unset.c \
		append.c \
		trunc.c \
		input.c \
		heredoc_utils.c \
		heredoc_utils2.c \
		add_to_history.c \
		free_all_and_exit.c \
		executor.c \
		hash_free.c \
		hash_tab.c \
		lexer_easy_splitter.c \
		lexer_spacer.c \
		lexer_spacer_utils.c \
		parser.c \
		parser_utils.c \
		redirect.c \
		token_constructor.c \
		token_constructor_utils.c \
		waitchild.c \
		isbuiltin.c \
		heredoc.c

OBJS = $(addprefix $(BUILDS)/, $(FILES:.c=.o))

DEP = $(OBJS:.o=.d)

LIBFT = $(LIBFTDIR)libft.a

#================= [DIRS] ===================
SRCS = ./srcs
VPATH = Built_ins essentials executor Hash_table  Lexer parser  redirections Tokenizer
VPATH := $(SRCS) $(addprefix $(SRCS)/, $(VPATH))
HEADER = ./includes ./libs/libft/includes
HEADER := $(addprefix -I, $(HEADER))
LIBFTDIR = ./libs/libft/
BUILDS = ./builds

#=================== [CONFIG_COMP] ==========
CC = cc
CFLAGS = -Wall -Werror -Wextra -g
DEPFLAGS = -MMD -MF

#===================== [COMMANDS] ===========
DEL = rm -rf
MKDIR = mkdir -p

#=====================[MESSAGES]=============

DEL_MSG				= @echo -n "[\e[0;31m DEL \e[0m] "
BIN_MSG				= @echo -n "[\e[0;32m BIN \e[0m] "
BLD_MSG				= @echo -n "[\e[0;34m BLD \e[0m] "
MKD_MSG				= @echo -n "[\e[0;35m MKD \e[0m] "

# =================[BASIC_RULES] ============

all: $(NAME)

$(NAME): $(LIBFT) $(BUILDS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(HEADER)  $(LIBFT) -o $(NAME) -lreadline

clean:
	$(DEL) $(BUILDS)
	@make clean -C $(LIBFTDIR)

fclean: clean
	$(DEL) ./minishell
	@make fclean -C $(LIBFTDIR)

re: fclean all

# =================[OTHER_RULES]============
$(BUILDS):
	@$(MKDIR) $@

$(BUILDS)/%.o:%.c
	$(BLD_MSG)
	@echo "Building ..." $@
	@$(CC) $(CFLAGS) -c $(HEADER) $< -o $@ $(DEPFLAGS) $(@:.o=.d)

$(LIBFT):
	@make -C $(LIBFTDIR)

test:$(NAME)
	./$(NAME)

t:test

v:all
	valgrind -q --leak-check=full --show-leak-kinds=all --suppressions=sup ./minishell

gdb:all
	gdb --tui minishell

# ============ [Target-sepecific Directives]==========
.PHONY: all clean fclean re test t v

# =============[Dependency Inclusion Directive] ======
-include ${DEP}
