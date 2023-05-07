/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:11:17 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 11:11:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <fcntl.h>

# include "libft.h"
# include "macros.h"

typedef enum e_lexeme
{
	LEX_IN_1,
	LEX_OUT_1,
	LEX_IN_2,
	LEX_OUT_2,
	LEX_SINGLE_QUOTES,
	LEX_DOUBLE_QUOTES,
	LEX_PIPE,
	LEX_TERM,
}	t_lexeme;

typedef enum e_operation
{
	READ,
	NEXT,
	RESET
}	t_operation;

typedef struct s_token
{
	char			*str;
	t_lexeme		type;
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
	int		in_fd;
	int		out_fd;
	int		exit_status;
	int		num_commands;
	char	*cwd;
	char	*input;
	char	*prompt;
	char	**path;
	char	**envp;
	int		**pipes;
	t_list	*envlist;
	t_list	*envtmp;
	t_list	*lexemes;
	t_ast	*ast;
}	t_ms;

void		update_envs(void);

//! Lexer
int			_lexer_push_token(char *str, t_lexeme lexeme);
int			_lexer_find_match(char *symbols, char *input);
void		lexer(void);

//! Token
t_token		*token_new(char *str, t_lexeme type);
t_token		*token_copy(t_token *token);
void		token_destroy(t_token *token);

//! Expansion
void		expander(void);
void		_expand_variable(t_token *token);

//! Parser
void		parser(void);
t_ast		*_parse_pipeline(void);
t_ast		*_parse_command(void);
t_ast		*_extend_pipeline(t_ast *ast, t_ast *command);

//! Scanner
t_token		*scanner(t_operation op);

//! Abstract Syntax Tree
t_ast		*ast_new(t_token *token);
t_ast		*ast_copy(t_ast *ast);
void		ast_insert(t_ast **ast, t_ast *node, bool left);
void		ast_clear(t_ast *ast);

//! Exit command
void		ft_exit(char **args);

//! Cd command
void		ft_cd(char **tokens);

//! Env command
void		ft_env(char **tokens);
char		*get_env(char *str);
t_list		*envlist(char **envp);

//! Echo command
void		ft_echo(char **tokens);

//! Export command
void		export_directly(t_list **envlist, char *assignment);
void		_export_from_temp_list(char *name);
void		ft_export(char **tokens);
bool		is_assignment(t_token *token);
char		**envlist_to_matrix(t_list *envlist);

//! Unset command
void		ft_unset(char **tokens);

//! Fake global
t_ms		*ms(void);

//! Pipeline
void		pipeline_create(void);
void		pipeline_apply(int cmd_index);
bool		is_unforkable(char *command);
bool		is_builtin(char *command);

//! Envlist
t_env		*env_new(char *key, char *value);
t_env		*env_copy(t_env	*env);
t_env		*_env_find(t_list *envlist, char *key);
bool		_env_key_cmp(t_env *env, char *key);
void		env_destroy(t_env *env);

//! Execution
void		execute(t_ast *ast);
void		_execute_forkable(t_ast *node);
void		_execute_command(char **args);
void		_execute_if_exists(char *exe, char **argv);
char		*get_executable_path(char *exe);

//! Path
char		*get_executable_path(char *exe);

//! Redirections
void		execute_redirection(t_lexeme type, char *filename);
int			heredoc(char *term);

//! IO
void		io_connect(void);
void		io_disconnect(int command_index);

//! Prompt
void		_compute(void);
void		reader(void);
char		*_update_prompt(void);

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
void		ft_free(void *p);
int			ft_strlen_sep(const char *s, char *seps);
void		sanitize(bool end);
int			is_spaces(char *str);
void		error(char *color, char *message, char *param, int status);

//! Matrix
void		matrix_destroy(void *matrix);
size_t		matrix_size(char **mat);
char		**matrix_append(char **m1, char *str);
char		**matrix_copy(char **matrix);

#endif
