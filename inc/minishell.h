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
int			lexer_push_token(char *str, t_lexeme lexeme);
int			lexer_find_match(char *symbols, char *input);
void		lexer(void);

//! Token
t_token		*token_new(char *str, t_lexeme type);
t_token		*token_copy(t_token *token);
void		token_destroy(void *token);

//! Parser
void		parser(void);
t_ast		*parse_pipeline(void);
t_ast		*parse_command(void);
t_ast		*extend_pipeline(t_ast *ast, t_ast *command);

//! Scanner
t_token		*scanner(t_operation op);

//! Abstract Syntax Tree
t_ast		*ast_new(t_token *token);
t_ast		*ast_copy(t_ast *ast);
void		ast_insert(t_ast **ast, t_ast *node, bool left);
void		ast_clear(t_ast *ast);

//! EXIT
void		ft_exit(char **args);

//! CD
void		ft_cd(char **tokens);

//! ENV
void		ft_env(char **tokens);
char		*get_env(char *str);
t_list		*envlist(char **envp);

//! ECHO
void		ft_echo(char **tokens);

//! EXPORT
void		export_directly(t_list **envlist, char *assignment);
void		export_from_temp_list(char *name);
void		ft_export(char **tokens);
bool		is_assignment(t_token *token);
char		**envlist_to_matrix(t_list *envlist);

//! UNSET
void		ft_unset(char **tokens);

//! Fake Global
t_ms		*ms(void);

//! Pipeline
void		create_all_pipes(void);
void		connect_io(void);
void		connect_pipeline(int cmd_index);
bool		is_unforkable(char *command);
bool		is_builtin(char *command);

//! Lists
t_env		*env_new(char *key, char *value);
t_env		*env_copy(t_env	*env);
t_env		*env_find(t_list *envlist, char *key);
bool		env_key_compare(t_env *env, char *key);
void		env_destroy(t_env *env);

//! Exec
void		execute(t_ast *ast);
void		execute_forkable(t_ast *node);
void		execute_command(char **args);
void		execute_if_exists(char *exe, char **argv);
char		*get_executable_path(char *exe);

//! Input
void		expander(void);
void		expand_variable(t_token *token);
void		compute(void);
void		reader(void);

//! Prompt

char		*update_prompt(void);

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
int			ft_strcmp(char *s1, char *s2);
void		ft_free(void *p);
int			ft_strlen_sep(const char *s, char *seps);
void		sanitize(bool end);
int			is_spaces(char *str);
void		matrix_destroy(void *matrix);
size_t		matrix_size(char **mat);
char		**matrix_append(char **m1, char *str);
char		**matrix_copy(char **matrix);
void		error(char *color, char *message, char *param, int status);
bool		ft_isnum(char *str);

#endif
