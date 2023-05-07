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

//! colors
# define CLR_BLACK		"\033[30m"
# define CLR_RED		"\033[31m"
# define CLR_GREEN		"\033[32m"
# define CLR_YELLOW		"\033[33m"
# define CLR_BLUE		"\033[34m"
# define CLR_MAGENTA	"\033[35m"
# define CLR_CYAN		"\033[36m"
# define CLR_GRAY		"\033[37m"
# define CLR_LRED		"\033[91m"
# define CLR_LGREEN		"\033[92m"
# define CLR_LYELLOW	"\033[93m"
# define CLR_LBLUE		"\033[94m"
# define CLR_LMAGENTA	"\033[95m"
# define CLR_LCYAN		"\033[96m"
# define CLR_WHITE		"\033[97m"
# define CLR_RST		"\033[0m"
# define CLR_BOLD		"\033[1m"
# define CLR_UNDERLINE	"\033[4m"

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
# define PROMPT_SYMBOL	"┖─ minishell ❯ "

//! pipes indexes
# define READ_END 	0
# define WRITE_END 	1

//! heredoc temporary file
# define HEREDOC	"heredoc.tmp"

//! debug
// # define DEBUG
// # define HERE		printf("HERE\n");
