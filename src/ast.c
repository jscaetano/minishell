/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:13:19 by marvin            #+#    #+#             */
/*   Updated: 2023/03/17 17:13:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*ast_new(t_token *token)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->token = token;
	return (node);
}

void	ast_insert_left(t_ast **ast, t_ast *node)
{
	if (*ast)
		(*ast)->left = node;
	else
		*ast = node;
}

void	ast_insert_right(t_ast **ast, t_ast *node)
{
	if (*ast)
		(*ast)->right = node;
	else
		*ast = node;
}

void    ast_traverse(t_ast *ast, void (*f)())
{
	if (!ast)
		return ;
	ast_traverse(ast->left, f);
	ast_traverse(ast->right, f);
	(*f)(&ast);
}

void    ast_destroy_node(t_ast ** node)
{
	#ifdef DEBUG
		printf("Token: \"%s\" (%zu)\n", (*node)->token->str, ft_strlen((*node)->token->str));
	#endif
	token_destroy((*node)->token);
	ft_free(*node);
	*node = NULL;
}

void	ast_print(t_ast *ast, int depth, void (*f)())
{
	if (!ast)
		return ;
	for (int i = 0; i < depth; i++)
		printf(" ");
	printf("[DEPTH %d]", depth);
	(*f)(ast->token);
	ast_print(ast->left, depth + 1, f);
	ast_print(ast->right, depth + 1, f);
}