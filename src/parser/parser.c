/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:33:50 by marvin            #+#    #+#             */
/*   Updated: 2023/03/17 17:33:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parser()
{
	t_ast	*root;

	scanner(RESET);
	root = parse_pipeline();
	return (root);
}

t_ast	*extend_pipeline(t_ast *ast, t_ast *command)
{
	t_ast	*root;

	root = ast_new(token_new(ft_strdup("|"), LEX_PIPE));
	if (!root)
		return (NULL);
	root->args = ft_calloc(1, sizeof(char *));
	ast_insert_left(&root, ast);
	ast_insert_right(&root, command);
	return (root);
}

t_ast	*parse_pipeline()
{
	t_ast	*root;
	t_ast	*command;

	command = NULL;
	root = parse_command();
	if (!root)
		return (NULL);
	while (scanner(READ)->type == LEX_PIPE)
	{
		scanner(NEXT);
		command = parse_command();
		root = extend_pipeline(root, command);
	}
	return (root);
}

t_ast	*parse_command()
{
	t_ast	*root;
	t_token	*curr;

	root = ast_new(token_copy(scanner(READ)));
	if (!root)
		return (NULL);
	root->args = ft_calloc(1, sizeof(char *));
	root->index = ms()->num_commands++;
	curr = scanner(READ);
	while (curr->type != LEX_PIPE)
	{
		root->args = matrix_append(root->args, curr->str);
		if (!scanner(NEXT))
			break;
		curr = scanner(READ);
	}
	return (root);
}