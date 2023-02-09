/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:03:07 by joacaeta          #+#    #+#             */
/*   Updated: 2023/02/09 21:34:44 by joacaeta         ###   ########.fr       */
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
	int		tokensfreed;
	t_env	*env;
	t_env	*tmp;
}	t_ms;

extern t_ms g_ms;

// ft_split.c
char		**ft_split(char const *s, char c);

// utils.c
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strlen(const char *s);
void		ft_free(void *p);
char		*ft_strndup(const char *s1, int size);

char		*ft_strdup(const char *s1);
void		no_leaks();



#endif
