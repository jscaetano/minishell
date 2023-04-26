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
	root->args = ft_calloc(1, sizeof(char *));
	ast_insert(&root, ast, true);
	ast_insert(&root, command, false);
	return (root);
}

t_ast	*parse_pipeline(void)
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

t_ast	*parse_command(void)
{
	t_ast	*command;
	t_token	*curr;

	command = ast_new(token_copy(scanner(READ)));
	if (!command)
		return (NULL);
	command->args = ft_calloc(1, sizeof(char *));
	command->index = ms()->num_commands++;
	curr = scanner(READ);
	while (curr->type != LEX_PIPE)
	{
		command->args = matrix_append(command->args, ft_strdup(curr->str));
		if (!scanner(NEXT))
			break ;
		curr = scanner(READ);
	}
	return (command);
}
