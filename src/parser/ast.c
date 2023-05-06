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
	node->args = ft_calloc(1, sizeof(char *));
	return (node);
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

void	ast_insert(t_ast **ast, t_ast *node, bool left)
{
	if (*ast && left)
		(*ast)->left = node;
	else if (*ast && !left)
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
	token_destroy(ast->token);
	matrix_destroy(ast->args);
	ft_free(ast);
}
