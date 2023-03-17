/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:10:59 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/17 19:03:22 by marvin           ###   ########.fr       */
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

void	token_print(t_token *token)
{
	if (!token)
		return ;
	if (token->type == LEX_IN_1)
		printf("[ < ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_1)
		printf("[ > ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_IN_2)
		printf("[ << ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_2)
		printf("[ >> ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_SINGLE_QUOTES)
		printf("[ '...' ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_DOUBLE_QUOTES)
		printf("[ \"...\" ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_RIGHT_PAR)
		printf("[ ( ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_LEFT_PAR)
		printf("[ ) ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_PIPE)
		printf("[ | ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_TERM)
		printf("[ ... ] -> \"%s\"\n", token->str);
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
		token_print(token);
		printf("args: \n");
		j = 0;
		while (token->args[j])
			printf("%s\n", token->args[j++]);
		token = token->next;
	}
}
