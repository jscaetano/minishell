/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:10:46 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/05/09 18:27:58 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_lexer_push_token(char *str, t_lexeme lexeme, bool can_merge)
{
	t_token	*token;

	token = token_new(str, lexeme, can_merge);
	if (!token || !str)
		return (0);
	ft_lstadd_back(&ms()->lexemes, ft_lstnew(token));
	return (ft_strlen(str));
}

// #ifdef DEBUG
// 	printf("\n\t---------------------------\n\n");
// 	printf("input: %s\n", input);
// 	printf("input[%d]: '%c'\n", tk_len, input[tk_len]);
// #endif
// #ifdef DEBUG
// 	printf("is_joinable: %d\n", is_joinable);
// #endif
int	_lexer_find_match(char *symbols, char *input)
{
	int		jump;
	char	*token;
	bool	can_merge;

	can_merge = false;
	jump = ft_strlen_sep(input, symbols);
	if (input[jump])
		if (!ft_strchr(SYMBOLS, input[jump + 1])
			&& ft_strchr("\'\"", input[jump]))
			can_merge = true;
	token = ft_substr(input, 0, jump);
	if (symbols[0] == '"')
		_lexer_push_token(token, LEX_DOUBLE_QUOTES, can_merge);
	else if (symbols[0] == '\'')
		_lexer_push_token(token, LEX_SINGLE_QUOTES, can_merge);
	else
		_lexer_push_token(token, LEX_TERM, can_merge);
	return (jump);
}

void	lexer(void)
{
	int	i;

	i = 0;
	while (ms()->input[i])
	{
		if (ms()->input[i] == ' ')
			i++;
		else if (ms()->input[i] == '|')
			i += _lexer_push_token(ft_strdup("|"), LEX_PIPE, false);
		else if (!ft_strncmp(&ms()->input[i], "<<", 2))
			i += _lexer_push_token(ft_strdup("<<"), LEX_IN_2, false);
		else if (!ft_strncmp(&ms()->input[i], ">>", 2))
			i += _lexer_push_token(ft_strdup(">>"), LEX_OUT_2, false);
		else if (ms()->input[i] == '<')
			i += _lexer_push_token(ft_strdup("<"), LEX_IN_1, false);
		else if (ms()->input[i] == '>')
			i += _lexer_push_token(ft_strdup(">"), LEX_OUT_1, false);
		else if (ms()->input[i] == '"')
			i += _lexer_find_match("\"", &ms()->input[i + 1]) + 2;
		else if (ms()->input[i] == '\'')
			i += _lexer_find_match("'", &ms()->input[i + 1]) + 2;
		else
			i += _lexer_find_match(SYMBOLS, &ms()->input[i]);
	}
}
