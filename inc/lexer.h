/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:36:33 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 20:36:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "macros.h"

/**
 * @brief An enum struct representing the different types of lexemes
 * recognized by the lexer. The lexer will use this enum to determine
 * when to split the input string into tokens.
 * 
 */
typedef enum e_lexeme
{
	LEX_IN_1,
	LEX_OUT_1,
	LEX_IN_2,
	LEX_OUT_2,
	LEX_PIPE,
	LEX_SINGLE_QUOTES,
	LEX_DOUBLE_QUOTES,
	LEX_TERM,
}	t_lexeme;

/**
 * @brief A struct representing a token. A token is a string of characters
 * that are recognized by the lexer as a single unit. 
 * @param str The string of characters that make up the token.
 * @param type The type of lexeme that the token is.
 */
typedef struct s_token
{
	char			*str;
	t_lexeme		type;
}	t_token;

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/= EXPANSION =\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Responsible for findind the name of a environment variable in a
 * string. This function is only called if a $ sign is found in the string.
 * For instance, if the $PATH variable is in the string it will return
 * a new string containing "$PATH".
 * 
 * @param str The string to search for.
 * @return char* A new pointer to the environment variable name.
 */
char		*_find_key(char *str);

/**
 * @brief Given a token, this function iterates over the string to search
 * for $ signs and expand them into their respective environment variables
 * values. For instance, if $SHELL is set to "/bin/zsh" and found
 * on the string, $SHELL is replaced with "/bin/zsh".
 * 
 * @param token The token to parse the string on
 */
void		_expand_variable(t_token *token);

/**
 * @brief Iterates of the lexeme list and checks if the current lexeme is 
 * LEX_TERM or LEX_DOUBLE_QUOTES. If so, it calls _expand_variable() on the
 * token.
 */
void		expander(void);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ LEXER _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief After the list of lexemes is generated, an intermediate step is
 * required to enforce the correct syntax of the input string.
 * 
 * @return true If the input's syntax is correct.
 * @return false Otherwise.
 */
bool		lexical_analysis(void);

/**
 * @brief Given a string and a type of lexeme, it creates a new pointer to
 * a t_token and pushes it to the lexeme list.
 * 
 * @param str The string of the token.
 * @param lexeme The type of lexeme that the token is.
 * @return int The number of characters to skip in the input string.
 */
int			_lexer_push_token(char *str, t_lexeme lexeme);

/**
 * @brief This function is set to find the match of a quote in string.
 * For instance, if the string is "Hello world", it will return the index
 * of the second quote. Also, if the symbols is set to SYMBOLS (defined in
 * macros.h), it will return the index of the first symbol found in the 
 * string. It also creates a new token out of it.
 * 
 * @param symbols The symbols to search for.
 * @param input The raw input string.
 * @return int The number of characters to skip in the input string.
 */
int			_lexer_find_match(char *symbols, char *input);

/**
 * @brief The lexer is one of the components of the shell. It is responsible
 * for splitting the input string into tokens. For instance, the string 
 * "ls > file" will be split into three tokens: "ls", ">" and "file",
 * creating a list with this format:
 * 	
 * 			[ls] 		-> [>] 			-> [file]
 * 			[LEX_TERM]  -> [LEX_OUT_1]  -> [LEX_TERM]
 */
void		lexer(void);

//! _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ TOKEN _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_

/**
 * @brief Creates a new pointer to a t_token.
 * 
 * @param str The string of the token.
 * @param type The type of lexeme that the token is.
 * @return t_token* A pointer to new t_token struct.
 * @return NULL If the allocation fails.
 */
t_token		*token_new(char *str, t_lexeme type);

/**
 * @brief Creates a new pointer to a copy of the token passed as argument.
 * 
 * @param token The token to copy
 * @return t_token* A pointer to the new t_token struct.
 * @return NULL If the allocation fails.
 */
t_token		*token_copy(t_token *token);

/**
 * @brief Frees the memory allocated for the token.
 * 
 * @param token The token to destroy.
 */
void		token_destroy(t_token *token);

#endif