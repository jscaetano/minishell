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

t_ast	*parse_pipeline(void)
{
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
	t_ast	*cmd;

	cmd = ast_new(token_copy(scanner(READ)));
	if (!cmd)
		return (NULL);
	cmd->index = ms()->num_commands++;
	while (scanner(READ) && scanner(READ)->type != LEX_PIPE)
	{
		// if (scanner(READ)->type >= LEX_IN_1 && scanner(READ)->type <= LEX_OUT_2)
		// 	cmd = extend_command(cmd, redirect);
		// else
		cmd->args = matrix_append(cmd->args, ft_strdup(scanner(READ)->str));
		scanner(NEXT);
	}
	return (cmd);
}

t_ast	*extend_command(t_ast *command)
{
	t_ast	*root;
	t_ast	*redirect;

	root = ast_new(token_copy(scanner(READ)));
	if (!root)
		return (NULL);
	ast_insert(&root, command, true);
	scanner(NEXT);
	redirect = ast_new(token_copy(scanner(READ)));
	if (!redirect)
		return (NULL);
	ast_insert(&root, redirect, false);
	scanner(NEXT);
	return (root);
}