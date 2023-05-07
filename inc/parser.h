/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:41:36 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 20:41:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "macros.h"
# include "lexer.h"

typedef enum e_operation
{
	READ,
	NEXT,
	RESET
}	t_operation;

typedef struct s_ast
{
	t_token			*token;
	char			**args;
	int				index;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

//! Abstract Syntax Tree
t_ast		*ast_new(t_token *token);
t_ast		*ast_copy(t_ast *ast);
void		ast_insert(t_ast **ast, t_ast *node, bool left);
void		ast_clear(t_ast *ast);

//! Parser
t_ast		*_extend_command(t_ast *command);
t_ast		*_extend_pipeline(t_ast *ast, t_ast *command);
t_ast		*_parse_command(void);
t_ast		*_parse_pipeline(void);
void		parser(void);

//! Scanner
t_token		*scanner(t_operation op);

#endif