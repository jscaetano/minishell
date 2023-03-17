/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:10:46 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/03/17 20:00:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *str, t_lex_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	return (token);
}

void	token_destroy(void *token)
{
	if (!token)
		return ;
	ft_free(((t_token *)token)->str);
	matrix_destroy(((t_token *)token)->args);
	ft_free(token);
}

void	token_push(char *str, t_lex_type lexeme)
{
	t_token	*token;

	token = token_new(str, lexeme);
	if (!token || !str)
		no_leaks(1);
	ft_lstadd_back(&ms()->lexemes, ft_lstnew(token));
}

void	lexer(t_ms *ms)
{
	int	i;
	int len;
	int	token_length;

	i = 0;
	len = ft_strlen(ms->input);
	while (i < len)
	{
		if (ms->input[i] == ' ')
			token_length = 1;
		else if (ms->input[i] == '|')
		{
			token_push(ft_strdup("|"), LEX_PIPE);
			token_length = 1;
		}
		else if (ms->input[i] == '<')
		{
			token_length = 1;
			if (ms->input[i + 1] == '<')
			{
				token_push(ft_strdup("<<"), LEX_IN_2);
				token_length++;
			}
			else
				token_push(ft_strdup("<"), LEX_IN_1);
		}
		else if (ms->input[i] == '>')
		{
			token_length = 1;
			if (ms->input[i + 1] == '>')
			{
				token_push(ft_strdup(">>"), LEX_OUT_2);
				token_length++;
			}
			else
				token_push(ft_strdup(">"), LEX_OUT_1);
		}
		else if (ms->input[i] == '"')
		{
			token_length = ft_strlen_delim(&ms->input[i + 1], '\"', 0) + 2;
			token_push(ft_substr(&ms->input[i], 0, token_length), LEX_DOUBLE_QUOTES);
		}
		else if (ms->input[i] == '\'')
		{
			token_length = ft_strlen_delim(&ms->input[i + 1], '\'', 0) + 2;
			token_push(ft_substr(&ms->input[i], 0, token_length), LEX_SINGLE_QUOTES);
		}
		else
		{
			token_length = ft_strlen_delim(&ms->input[i], 0, 1);
			token_push(ft_substr(&ms->input[i], 0, token_length), LEX_TERM);
		}
		i += token_length;
	}
}
