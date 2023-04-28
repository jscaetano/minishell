/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:10:59 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/28 16:31:10 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for testing purposes, print tmp list
void	printtmp(void)
{
	t_list	*curr;
	t_env	*tmp;

	curr = ms()->new_tmp;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		curr = curr->next;
	}
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

void	ast_debug(t_ast *ast, int depth, void (*f)())
{
	int	i;

	i = -1;
	if (!ast)
		return ;
	while (++i < depth)
		printf(" ");
	printf("[DEPTH %d][INDEX %d]\n", depth, ast->index);
	(*f)(ast->token);
	ast_debug(ast->left, depth + 1, f);
	ast_debug(ast->right, depth + 1, f);
}
