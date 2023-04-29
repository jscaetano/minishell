/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:10:46 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/04/29 11:25:57 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer_push_token(char *str, t_lex_type lexeme)
{
	t_token	*token;

	token = token_new(str, lexeme);
	if (!token || !str)
		return (0);
	ft_lstadd_back(&ms()->lexemes, ft_lstnew(token));
	return (ft_strlen(str));
}

int	lexer_find_match(char *symbols, char *input)
{
	int		token_length;
	char	*value;

	token_length = ft_strlen_sep(input, symbols);
	value = ft_substr(input, 0, token_length);
	if (symbols[0] == '"')
		lexer_push_token(value, LEX_DOUBLE_QUOTES);
	else if (symbols[0] == '\'')
		lexer_push_token(value, LEX_SINGLE_QUOTES);
	else
		lexer_push_token(value, LEX_TERM);
	return (token_length);
}

void	lexer()
{
	int	i;

	i = 0;
	while (ms()->input[i])
	{
		if (ms()->input[i] == ' ')
			i++;
		else if (ms()->input[i] == '|')
			i += lexer_push_token(ft_strdup("|"), LEX_PIPE);
		else if (!ft_strncmp(&ms()->input[i], "<<", 2))
			i += lexer_push_token(ft_strdup("<<"), LEX_IN_2);
		else if (!ft_strncmp(&ms()->input[i], ">>", 2))
			i += lexer_push_token(ft_strdup(">>"), LEX_OUT_2);
		else if (ms()->input[i] == '<')
			i += lexer_push_token(ft_strdup("<"), LEX_IN_1);
		else if (ms()->input[i] == '>')
			i += lexer_push_token(ft_strdup(">"), LEX_OUT_1);
		else if (ms()->input[i] == '"')
			i += lexer_find_match("\"", &ms()->input[i + 1]) + 2;
		else if (ms()->input[i] == '\'')
			i += lexer_find_match("'", &ms()->input[i + 1]) + 2;
		else
			i += lexer_find_match(SYMBOLS, &ms()->input[i]);
	}
}
