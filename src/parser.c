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

	root = parse_pipeline();
	scanner(RESET);
	return (root);
}

t_ast	*append_pipeline(t_ast *ast, t_ast *command)
{
	t_ast	*root;

	root = ast_new(token_new(ft_strdup("|"), LEX_PIPE));
	if (!root)
		return (NULL);
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
		root = append_pipeline(root, command);
	}
	return (root);
}

t_ast	*parse_command()
{
	t_ast	*root;

	root = ast_new(scanner(READ));
	if (!root)
		return (NULL);
	scanner(NEXT);
	return (root);
}