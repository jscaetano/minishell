/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crypto <crypto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:10:59 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/17 16:54:04 by crypto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for testing purposes, print tmp list
void	printtmp(void)
{
	t_var	*tmp;

	tmp = ms()->tmp->top;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	printf("%s=%s\n", tmp->name, tmp->content);
}

void	print_token(t_token *token)
{
	if (token->type == LEX_IN_1)
		printf("[ LEX_IN_REDIR_1 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_1)
		printf("[ LEX_OUT_REDIR_1 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_IN_2)
		printf("[ LEX_IN_REDIR_2 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_2)
		printf("[ LEX_OUT_REDIR_2 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_SINGLE_QUOTES)
		printf("[ LEX_SINGLE_QUOTES ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_DOUBLE_QUOTES)
		printf("[ LEX_DOUBLE_QUOTES ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_RIGHT_PAR)
		printf("[ LEX_RIGHT_PAR ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_LEFT_PAR)
		printf("[ LEX_LEFT_PAR ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_PIPE)
		printf("[ LEX_PIPE ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_TERM)
		printf("[ LEX_TERM ] -> \"%s\"\n", token->str);
}

void	print_lexer_args()
{
	t_token	*token;
	int		i;
	int		j;

	i = 1;
	j = 0;
	token = ms()->lexer.head;
	while (token)
	{
		printf("[%2d]", i++);
		print_token(token);
		printf("args: \n");
		j = 0;
		while (token->args[j])
			printf("%s\n", token->args[j++]);
		token = token->next;
	}
}
