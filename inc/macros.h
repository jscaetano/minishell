/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 11:56:40 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 11:56:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H
# define MACROS_H

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

//! colors
# define ANSI_BLACK		"\033[30m"
# define ANSI_RED		"\033[31m"
# define ANSI_GREEN		"\033[32m"
# define ANSI_YELLOW	"\033[33m"
# define ANSI_BLUE		"\033[34m"
# define ANSI_MAGENTA	"\033[35m"
# define ANSI_CYAN		"\033[36m"
# define ANSI_GRAY		"\033[37m"
# define ANSI_LRED		"\033[91m"
# define ANSI_LGREEN	"\033[92m"
# define ANSI_LYELLOW	"\033[93m"
# define ANSI_LBLUE		"\033[94m"
# define ANSI_LMAGENTA	"\033[95m"
# define ANSI_LCYAN		"\033[96m"
# define ANSI_WHITE		"\033[97m"
# define ANSI_RST		"\033[0m"
# define ANSI_BOLD		"\033[1m"
# define ANSI_UNDERLINE	"\033[4m"

//! minishell errors
# define ERROR_UNKNOWN_CMD		"minishell: command not found: "
# define ERROR_UNKNOWN_FILE		"minishell: no such file or directory: "

//! cd errors
# define ERROR_CD_WRONG_DIR		"cd: no such file or directory: "
# define ERROR_CD_MANY_ARGS		"cd: too many arguments"

//! exit errors
# define ERROR_EXIT_NO_NUM		"exit: numeric argument required"
# define ERROR_EXIT_MANY_ARGS	"exit: too many arguments"

//! lexer symbols
# define SYMBOLS	"<>\'\"| "

//! minishell symbols
# define PROMPT_UPPER	"┎─── "
# define PROMPT_LOWER	"┖─ minishell ❯ "

//! pipes indexes
# define READ_END 	0
# define WRITE_END 	1

//! heredoc temporary file
# define HEREDOC	"heredoc.tmp"

//! debug
// # define DEBUG
// # define HERE		printf("HERE\n");

#endif
