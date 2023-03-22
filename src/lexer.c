/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:10:46 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/03/22 20:11:30 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *str, t_lex_type type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	return (token);
}

char **	matrix_copy(char **matrix)
{
	char **dup;
	size_t	i;

	i = 0;
	while (matrix[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (matrix[++i])
		dup[i] = ft_strdup(matrix[i]);
	return (dup);
}

t_token * token_copy(t_token * token)
{
	t_token	*dup;
	size_t	i;

	i = 0;
	dup = token_new(ft_strdup(token->str), token->type);
	if (!dup)
		return (NULL);
	if (token->args)
		dup->args = matrix_copy(token->args);
	return (dup);
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
		// printf("i : %d\n", i);
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
			token_length = ft_strlen_sep(&ms->input[i + 1], "\"") + 2;
			//((t_token *)ft_lstlast(ms->lexemes)->content)->str = ft_strjoin(((t_token *)ft_lstlast(ms->lexemes)->content)->str, ft_substr(&ms->input[i], 0, token_length));
			token_push(ft_substr(&ms->input[i + 1], 0, token_length - 2), LEX_DOUBLE_QUOTES);
		}
		else if (ms->input[i] == '\'')
		{
			token_length = ft_strlen_sep(&ms->input[i + 1], "\'") + 2;
			//((t_token *)ft_lstlast(ms->lexemes)->content)->str = ft_strjoin(((t_token *)ft_lstlast(ms->lexemes)->content)->str, ft_substr(&ms->input[i], 0, token_length));
			token_push(ft_substr(&ms->input[i + 1], 0, token_length - 2), LEX_SINGLE_QUOTES);
		}
		else
		{
			token_length = ft_strlen_sep(&ms->input[i], " ");
			token_push(ft_substr(&ms->input[i], 0, token_length), LEX_TERM);
		}
		i += token_length;
	}
}
