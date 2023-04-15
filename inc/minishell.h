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

# define INPUT_LEN	1000
# define PROMPT		"\033[38;5;13mft_shell > \033[0m"
# define SYMBOLS	"<>\'\"| "
# define DEBUG
# define HERE		printf("HERE\n");

typedef enum s_lex_type
{
	LEX_IN_1,				// <
	LEX_OUT_1,				// >
	LEX_IN_2,				// <<
	LEX_OUT_2,				// >>
	LEX_SINGLE_QUOTES,		// '
	LEX_DOUBLE_QUOTES,		// "
	LEX_PIPE,				// |
	LEX_VARIABLE,			// $
	LEX_TERM,				// anything else
	LEX_RIGHT_PAR,			// (
	LEX_LEFT_PAR,			// )
}t_lex_type;

typedef enum s_scanner_op
{
	READ,
	NEXT,
	RESET
} t_scanner_op;

typedef struct s_token
{
	char			*str;
	char			**args;
	t_lex_type		type;
}t_token;

typedef struct s_ast
{
	t_token			*token;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}t_ast;

typedef struct s_var
{
	char			*name;
	char			*content;
	struct s_var	*next;
}	t_var;

typedef struct s_env
{
	int				size;
	struct s_var	*top;
}	t_env;

typedef struct s_ms
{
	char	*cwd;
	int		laststatus;
	char	*input;
	char	**tokens;
	char	**path;
	char	**envv;
	int		tokensfreed;
	t_env	*env;
	t_env	*tmp;
	t_list	*lexemes;
	t_ast	*ast;
}t_ms;

// utils
char		*ft_strndup(const char *s1, int size);
char		*ft_strcpy(char *dest, char *src);
char		*ft_strncpy(char *dest, char *src, int size);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
void		ft_free(void *p);
int			ft_strlen_sep(const char *s, char *seps);
int			ft_strlen_sep_alnum(const char *s);
void		no_leaks(int end);
void		matrix_destroy(void *matrix);
size_t		matrix_size(char **mat);
char		**matrix_append(char **m1, char *str);
int			is_spaces(char *str);

//! Scanner
t_token		*scanner(t_scanner_op op);

//! Abstract Syntax Tree
t_ast		*ast_new(t_token *token);
void		ast_insert_left(t_ast **ast, t_ast *node);
void		ast_insert_right(t_ast **ast, t_ast *node);
void		ast_postorder_traverse(t_ast *ast, void (*f)());
void    	ast_destroy_node(t_ast ** node);
void		ast_print(t_ast *ast, int depth, void (*f)());

//! Lexer
t_token		*token_new(char *str, t_lex_type type);
t_token		*token_copy(t_token * token);
void		token_destroy(void *token);
void		token_push(char *str, t_lex_type lexeme);
void		lexer(t_ms *ms);

//! Parser
t_ast		*parser();
t_ast		*parse_pipeline();
t_ast		*parse_command();

//cd
void		ft_cd(char **tokens);

//env
t_env		*envlist(char **envv);
char		*get_env(char *str);
void		ft_env(void);

//fake global
t_ms		*ms(void);

//export unset
void		ft_export(char **tokens);
void		ft_unset(char **tokens);
int			find_equals(int token_to_check);

//lists
void		ft_stackpush(t_env *env, char *equal);
t_env		*ft_stacknew(void);

//exec
void		exec(char *pathtoexe, char **argv);
void		exec_if_exists(char *exe, char **argv);

//input
void		handle_input(void);
void		read_input(void);

//echo
void		ft_echo(char **tokens);

//testing
void		printtmp(void);
void		lexer_debug();
void		matrix_debug(char **matrix);
void		token_debug(t_token *token);

#endif
