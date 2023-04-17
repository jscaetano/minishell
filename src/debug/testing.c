/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:10:59 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/17 10:39:00 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for testing purposes, print tmp list
void	printtmp(void)
{
	t_var	*tmp;

	tmp = ms()->tmp->top;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	printf("%s=%s\n", tmp->name, tmp->content);
}

void	matrix_debug(char **matrix)
{
	if (!matrix)
		return ;
	size_t	i;

	i = -1;
	while (matrix[++i])
		printf("matrix[%zu] = \"%s\"\n", i, matrix[i]);
}

void	token_debug(t_token *token)
{
	if (!token)
		return ;
	if (token->type == LEX_IN_1)
		printf("[ IN ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_1)
		printf("[ OUT ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_IN_2)
		printf("[ IN 2 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_2)
		printf("[ OUT 2 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_SINGLE_QUOTES)
		printf("[ SQUOTES ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_DOUBLE_QUOTES)
		printf("[ DQUOTES ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_RIGHT_PAR)
		printf("[ LPAR ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_LEFT_PAR)
		printf("[ RPAR ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_PIPE)
		printf("[ PIPE ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_TERM)
		printf("[ TERM ] -> \"%s\"\n", token->str);
}

void	lexer_debug()
{
	t_list	*node;
	t_token	*token;
	int		i;

	i = 1;
	node = ms()->lexemes;
	while (node)
	{
		token = (t_token *)node->content;
		printf("[%2d]", i++);
		token_debug(token);
		node = node->next;
	}
}
