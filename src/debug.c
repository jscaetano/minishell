/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 18:14:49 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/03/04 18:15:03 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	if (token->type == LEX_IN_REDIR_1)
		printf("[ LEX_IN_REDIR_1 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_REDIR_1)
		printf("[ LEX_OUT_REDIR_1 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_IN_REDIR_2)
		printf("[ LEX_IN_REDIR_2 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_REDIR_2)
		printf("[ LEX_OUT_REDIR_2 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_SINGLE_QUOTES)
		printf("[ LEX_SINGLE_QUOTES ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_DOUBLE_QUOTES)
		printf("[ LEX_DOUBLE_QUOTES ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_RIGHT_PAR)
		printf("[ LEX_RIGHT_PAR ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_LEFT_PAR)
		printf("[ LEX_LEFT_PAR ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_PIPE)
		printf("[ LEX_PIPE ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_TERM)
		printf("[ LEX_TERM ] -> \"%s\"\n", token->str);
}

void	print_lexer(t_lexer *lexer)
{	
	int		i;
	t_token	*token;
	
	i = 1;
	token = lexer->head;
	while (token)
	{	
		printf("[%2d]", i++);
		print_token(token);
		token = token->next;
	}
}