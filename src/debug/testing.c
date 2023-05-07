/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:10:59 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/07 20:25:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printtmp(void)
{
	t_list	*curr;
	t_env	*tmp;

	curr = ms()->envtmp;
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
	size_t	i;

	if (!matrix)
		return ;
	i = -1;
	while (matrix[++i])
		printf("matrix[%zu] = \"%s\"\n", i, matrix[i]);
}

void	token_debug(t_token *token)
{
	if (!token)
		return ;
	if (token->type == LEX_IN_1)
		printf(ANSI_BLUE "[ IN ] -> " ANSI_RST "\"%s\"\n", token->str);
	else if (token->type == LEX_OUT_1)
		printf(ANSI_BLUE "[ OUT ] -> " ANSI_RST "\"%s\"\n", token->str);
	else if (token->type == LEX_IN_2)
		printf(ANSI_YELLOW "[ IN 2 ] -> " ANSI_RST "\"%s\"\n", token->str);
	else if (token->type == LEX_OUT_2)
		printf(ANSI_YELLOW "[ OUT 2 ] -> " ANSI_RST "\"%s\"\n", token->str);
	else if (token->type == LEX_SINGLE_QUOTES)
		printf(ANSI_GREEN "[ SQUOTES ] -> " ANSI_RST "\"%s\"\n", token->str);
	else if (token->type == LEX_DOUBLE_QUOTES)
		printf(ANSI_GREEN "[ DQUOTES ] -> " ANSI_RST "\"%s\"\n", token->str);
	else if (token->type == LEX_PIPE)
		printf(ANSI_RED "[ PIPE ] -> " ANSI_RST "\"%s\"\n", token->str);
	else if (token->type == LEX_TERM)
		printf("[ TERM ] -> \"%s\"\n", token->str);
}

void	lexer_debug(void)
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
	ast_debug(ast->right, depth + 1, f);
	while (++i < 5 * depth)
		printf(" ");
	printf("[%d]", depth);
	(*f)(ast->token);
	ast_debug(ast->left, depth + 1, f);
}
