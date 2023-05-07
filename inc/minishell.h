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

# include "lexer.h"
# include "parser.h"
# include "commands.h"
# include "env.h"
# include "macros.h"

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

//! Execution
void		_execute_if_exists(char *exe, char **argv);
void		_execute_command(char **args);
void		_execute_forkable(t_ast *node);
void		_execute_pipeline(t_ast *node);
void		execute(t_ast *ast);

//! IO
void		io_connect(void);
void		io_disconnect(int command_index);

//! Path
char		*get_executable_path(char *exe);

//! Pipeline
void		pipeline_create(void);
void		pipeline_apply(int cmd_index);
bool		is_unforkable(char *command);
bool		is_builtin(char *command);

//! Redirections
int			heredoc(char *term);
void		execute_redirection(t_lexeme type, char *filename);

//! Signals
void		handler_sigint(int signum);
void		handler_child(int signum);
void		signals_heredoc(void);
void		signals_child(void);
void		signals(void);

//! Fake global
t_ms		*ms(void);

//! Matrix
void		matrix_destroy(void *matrix);
size_t		matrix_size(char **mat);
char		**matrix_append(char **m1, char *str);
char		**matrix_copy(char **matrix);

//! Sanitize
void		ft_free(void *p);
void		sanitize(bool end);
void		update_envs(void);

//! Utils
int			ft_strlen_sep(const char *s, char *seps);
int			is_spaces(char *str);
void		error(char *color, char *message, char *param, int status);

//! Testing
void		printtmp(void);
void		matrix_debug(char **matrix);
void		token_debug(t_token *token);
void		lexer_debug(void);
void		ast_debug(t_ast *ast, int depth, void (*f)());

//! Input
char		*_update_prompt(void);
void		_compute(void);
void		reader(void);

//! Main
void		_ms_init(char **envv);

#endif
