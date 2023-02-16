/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:03:07 by joacaeta          #+#    #+#             */
/*   Updated: 2023/02/16 18:51:27 by ncarvalh         ###   ########.fr       */
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

typedef enum s_lexemes
{
	LEX_IN_REDIR_1,			// <
	LEX_OUT_REDIR_1,		// >
	LEX_IN_REDIR_2,			// <<
	LEX_OUT_REDIR_2,		// >>
	LEX_SINGLE_QUOTES,		// '
	LEX_DOUBLE_QUOTES,		// "
	LEX_RIGHT_PAR,			// (
	LEX_LEFT_PAR,			// )
	LEX_VARIABLE,			// $
	LEX_PIPE,				// |
	LEX_TERM,				// anything else
}t_lexeme;

typedef struct s_token{
	char			*str;
	t_lexeme		type;
	struct s_token	*next;
}t_token;

typedef struct s_lexer
{
	t_token	*head;
	int		n;	
}t_lexer;

typedef struct s_ms
{
	char	*cwd;
	char	*input;
	char	**tokens;
	char	**path;
	int		tokensfreed;
	char	**env;
	t_lexer	lexer;
}	t_ms;

extern t_ms g_ms;

// ft_split.c
char		**ft_split(char const *s, char c);


// utils.c
int			ft_strcmp(char *s1, char *s2);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

int			ft_strlen(const char *s);

int			ft_strclen(const char *s, char c);

void		ft_free(void *p);

char		*ft_substr(char const *s, int start, int len);

char		*ft_strdup(const char *s1);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		no_leaks();


//!_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= LEXER =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

t_lexer	new_lexer(int n);

t_token	*new_token(char *str, t_lexeme type);

void	destroy_token(t_token *token);

void	destroy_lexer(t_lexer *lexer);

void	lexer(t_ms *ms);

void	print_lexer(t_lexer *lexer);

#endif
