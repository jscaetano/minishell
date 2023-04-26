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

void	ast_clear(t_ast *ast)
{
	if (!ast)
		return ;
	ast_clear(ast->left);
	ast_clear(ast->right);
	ast_destroy_node(ast);
}

void    ast_destroy_node(t_ast *node)
{
	token_destroy(node->token);
	matrix_destroy(node->args);
	ft_free(node);
}

void	ast_print(t_ast *ast, int depth, void (*f)())
{
	if (!ast)
		return ;
	for (int i = 0; i < depth; i++)
		printf(" ");
	printf("[DEPTH %d][INDEX %d]\n", depth, ast->index);
	(*f)(ast->token);
	ast_print(ast->left, depth + 1, f);
	ast_print(ast->right, depth + 1, f);
}

t_ast	*ast_copy(t_ast *ast)
{
	t_ast	*dup;

	dup = ast_new(token_copy(ast->token));
	if (!dup)
		return (NULL);
	dup->args = matrix_copy(ast->args);
	dup->index = ast->index;
	return (dup);
}

t_list	*ast_to_list(t_ast *ast)
{
	t_list	*cmd_list;
	t_list	*curr;

	if (!ast)
		return (NULL);
	if (ast->token->type == LEX_TERM)
		return (ft_lstnew(ast_copy(ast)));
	cmd_list = ast_to_list(ast->left);
	curr = cmd_list;
	while (curr->next)
		curr = curr->next;
	curr->next = ast_to_list(ast->right);
	return (cmd_list);
}