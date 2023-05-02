/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:03:07 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/02 19:36:38 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <signal.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# include "libft.h"

# define CLR_RED	"\033[38;5;1m"
# define CLR_GREEN	"\033[38;5;47m"
# define CLR_BLUE	"\033[0;34m"
# define CLR_CYAN	"\033[38;5;14m"
# define CLR_YELLOW	"\033[33m"
# define CLR_PURPLE	"\033[38;5;13m"
# define CLR_WHITE	"\033[0;37m"
# define CLR_BLACK	"\033[0;30m"
# define CLR_RST	"\033[0m"

# define ERROR_UNKNOWN_DIR	"cd: no such file or directory: "
# define ERROR_UNKNOWN_CMD	"minishell: command not found: "

# define INPUT_LEN	1000
# define PROMPT		"\033[38;5;13mminishell > \033[0m"
# define SYMBOLS	"<>\'\"| "
# define READ_END 	0
# define WRITE_END 	1
// # define DEBUG
# define HERE		printf("HERE\n");

typedef enum e_exit_status
{
	EXIT_OK = 0,
	EXIT_FAIL = 1,
	EXIT_INCORRECT_USAGE = 2,
	EXIT_UNKNOWN_COMMAND = 127,
	EXIT_SIGINT = 130
}	t_exit_status;

typedef enum e_lex_type
{
	LEX_IN_1,
	LEX_OUT_1,
	LEX_IN_2,
	LEX_OUT_2,
	LEX_SINGLE_QUOTES,
	LEX_DOUBLE_QUOTES,
	LEX_PIPE,
	LEX_VARIABLE,
	LEX_TERM,
	LEX_RIGHT_PAR,
	LEX_LEFT_PAR,
}	t_lex_type;

typedef enum e_scanner_op
{
	READ,
	NEXT,
	RESET
}	t_scanner_op;

typedef struct s_token
{
	char			*str;
	t_lex_type		type;
}	t_token;

typedef struct s_ast
{
	t_token			*token;
	char			**args;
	int				index;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_env
{
	char			*key;
	char			*value;
}	t_env;

typedef struct s_ms
{
	char	*cwd;
	int		laststatus;
	char	*input;
	char	**path;
	char	**envv;
	int		num_commands;
	int		**pipes;
	t_list	*env;
	t_list	*tmp;
	t_list	*lexemes;
	t_ast	*ast;
	t_list	*cmd_list;
}	t_ms;

//! Lexer
int			lexer_push_token(char *str, t_lex_type lexeme);
int			lexer_find_match(char *symbols, char *input);
void		lexer(void);

//! Token
t_token		*token_new(char *str, t_lex_type type);
t_token		*token_copy(t_token * token);
void		token_destroy(void *token);

//! Parser
void		parser(void);
t_ast		*parse_pipeline(void);
t_ast		*parse_command(void);
t_ast		*extend_pipeline(t_ast *ast, t_ast *command);

//! Scanner
t_token		*scanner(t_scanner_op op);

//! Abstract Syntax Tree
t_ast		*ast_new(t_token *token);
t_ast		*ast_copy(t_ast *ast);
void		ast_insert(t_ast **ast, t_ast *node, bool left);
void		ast_clear(t_ast *ast);
t_list		*ast_to_list(t_ast *ast);

//! CD
void		ft_cd(char **tokens);

//! ENV
void		ft_env(void);
char		*get_env(char *str);
t_list		*envlist(char **envp);

//! ECHO
void		ft_echo(char **tokens);

//! EXPORT UNSET
void		export_directly(t_list **envlist, char *assignment);
void		export_from_temp_list(char *name);
void		ft_export(char **tokens);
void		ft_unset(char **tokens);
bool		is_assignment(int token_to_check);

//! Fake Global
t_ms		*ms(void);

//! Pipeline
void		create_all_pipes(void);
void		connect_pipeline(int cmd_index);
bool		is_unforkable(char *command);
bool		is_builtin(char *command);

//! Lists
t_env		*env_new(char *key, char *value);
t_env		*env_copy(t_env	*env);
t_env		*env_find(t_list *envlist, char *key);
bool 		env_key_compare(t_env *env, char *key);
void		env_destroy(t_env *env);

//! Exec
void		execute_command_list(t_list *cmd_list);
void		execute_forkable(t_ast *node);
void		execute_command(char **args);
void		execute_if_exists(char *exe, char **argv);
char		*get_executable_path(char *exe);

//! Input
void		expander(void);
void		expand_variable(t_token *token);
void		handle_input(void);
void		read_input(void);

//! Prompt

char		*update_prompt();

//! Testing
void		printtmp(void);
void		lexer_debug(void);
void		matrix_debug(char **matrix);
void		token_debug(t_token *token);
void		ast_debug(t_ast *ast, int depth, void (*f)());

//! Signals
void		signals(void);
void		signals_child(void);
void		signals_heredoc(void);
void		handler_sigint(int signum);
void		handler_child(int signum);

//! Utils
char		*ft_strndup(const char *s1, int size);
int			ft_strcmp(char *s1, char *s2);
void		ft_free(void *p);
int			ft_strlen_sep(const char *s, char *seps);
int			ft_strlen_sep_alnum(const char *s);
void		sanitize(bool end);
int			is_spaces(char *str);
void		matrix_destroy(void *matrix);
size_t		matrix_size(char **mat);
char		**matrix_append(char **m1, char *str);
char		**matrix_copy(char **matrix);
void		message(char *color, char *message, char *param);

#endif
