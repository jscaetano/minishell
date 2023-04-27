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

void	parser(void)
{
	scanner(RESET);
	ms()->ast = parse_pipeline();
	ms()->cmd_list = ast_to_list(ms()->ast);
}

t_ast	*extend_pipeline(t_ast *ast, t_ast *command)
{
	t_ast	*root;

	root = ast_new(token_new(ft_strdup("|"), LEX_PIPE));
	if (!root)
		return (NULL);
	ast_insert(&root, ast, true);
	ast_insert(&root, command, false);
	return (root);
}

// t_ast	*extend_redirect(t_ast *ast, t_ast *redirection)
// {
// 	t_ast	*root;

// 	root = ast_new(token_new(ft_strdup()))
// }

t_ast	*parse_pipeline(void)
{
	// t_ast	*root;
	t_ast	*ast;
	t_ast	*command;

	command = NULL;
	ast = parse_command();
	if (!ast)
		return (NULL);
	while (scanner(READ) && scanner(READ)->type == LEX_PIPE)
	{
		scanner(NEXT);
		command = parse_command();
		ast = extend_pipeline(ast, command);
	}
	return (ast);
}

t_ast	*parse_command(void)
{
	t_ast	*root;
	// t_ast	*redirect;
	t_token	*curr;

	root = ast_new(token_copy(scanner(READ)));
	if (!root)
		return (NULL);
	root->index = ms()->num_commands++;
	curr = scanner(READ);
	while (curr && curr->type != LEX_PIPE)
	{
		// if (curr->type >= LEX_IN_1 && curr->type <= LEX_OUT_2)
		// {
		// 	scanner(NEXT);
		// 	redirect = parse_redirection();
		// 	root = extend_command(root, redirect);
		// }
		// if (!scanner(NEXT))
		// 	break ;
		root->args = matrix_append(root->args, ft_strdup(curr->str));
		scanner(NEXT);
		curr = scanner(READ);
	}
	return (root);
}

// t_ast	*parse_redirection(void)
// {
// 	t_ast	*redirect;
// 	t_token	*curr;

// 	redirect = ast_new(token_copy(scanner(READ)));
// 	if (!redirect)
// 		return (NULL);
// 	curr = scanner(READ);
// 	redirect->args = matrix_append(redirect->args, ft_strdup(curr->str));
// 	return (redirect);
// }
