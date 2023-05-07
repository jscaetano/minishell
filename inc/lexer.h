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

typedef struct s_token
{
	char			*str;
	t_lexeme		type;
}	t_token;

//! Expansion
char		*_find_key(char *str);
void		_expand_variable(t_token *token);
void		expander(void);

//! Lexer
int			_lexer_push_token(char *str, t_lexeme lexeme);
int			_lexer_find_match(char *symbols, char *input);
void		lexer(void);

//! Token
t_token		*token_new(char *str, t_lexeme type);
t_token		*token_copy(t_token *token);
void		token_destroy(t_token *token);

#endif