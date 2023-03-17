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
// # define DEBUG

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

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_token
{
	char			*str;
	char			**args;
	t_lex_type		type;
}t_token;

typedef struct s_ast
{
	void			*content;
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
	char	*input;
	char	**tokens;
	char	**path;
	char	**envv;
	int		tokensfreed;
	t_env	*env;
	t_env	*tmp;
	t_list	*lexemes;
}	t_ms;

// ft_split
char		**ft_split(char const *s, char c);

// utils
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(const char *s);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_substr(char const *s, int start, int len);
void		ft_free(void *p);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_strlen_delim(const char *s, char delim, int symbols);
char		*ft_strndup(const char *s1, int size);
char		*ft_strdup(const char *s1);
void		no_leaks(int end);
void		matrix_destroy(void *matrix);
t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));

//! Scanner
t_token		*scanner(t_scanner_op op);

//! Abstract Syntax Tree
t_ast		*ast_new(void *content);
void		ast_insert_left(t_ast **ast, t_ast *node);
void		ast_insert_right(t_ast **ast, t_ast *node);
void		ast_traverse(t_ast **ast, void (*f)());
void		ast_print(t_ast *ast, int depth, void (*f)());

//! Lexer
t_token		*token_new(char *str, t_lex_type type);
void		token_destroy(void *token);
void		token_push(char *str, t_lex_type lexeme);
void		lexer(t_ms *ms);

//! Parser
t_ast		*parser();
t_ast		*parse_pipeline();
t_ast		*parse_command();

//cd
void		ft_cd(void);

//env
t_env		*envlist(char **envv);
char		*get_env(char *str);
void		ft_env(void);

//fake global
t_ms		*ms(void);

//export unset
void		ft_export(void);
void		ft_unset(void);
int			find_equals(void);

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
void		ft_echo(int flag);

//testing
void		printtmp(void);
void		print_lexer_args();
void		token_print(t_token *token);

#endif
