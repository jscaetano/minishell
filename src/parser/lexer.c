/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:10:46 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/05/08 09:59:37 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	lexical_analysis(void)
{
	t_token	*next;
	int		num_pipes;
	int		num_commands;

	num_pipes = 0;
	num_commands = 1;
	scanner(RESET);
	if (is_special_token(scanner(READ)))
		return (error(ANSI_RED, ERROR_SYNTAX, scanner(READ)->str, 2));
	while (scanner(READ))
	{
		next = scanner(LOOKAHEAD);
		if (is_redirection(scanner(READ)) && (!next || is_special_token(next)))
			return (error(ANSI_RED, ERROR_UNCLOSED_RED, NULL, 2));
		if (scanner(READ)->type == LEX_PIPE)
		{
			num_pipes++;
			if (next && !is_special_token(next))
				num_commands++;
			scanner(NEXT);
		}
	}
	if (num_pipes >= num_commands)
		return (error(ANSI_RED, ERROR_UNCLOSED_PIPES, NULL, 2));
	return (true);
}

int	_lexer_push_token(char *str, t_lexeme lexeme)
{
	t_token	*token;

	token = token_new(str, lexeme);
	if (!token || !str)
		return (0);
	ft_lstadd_back(&ms()->lexemes, ft_lstnew(token));
	return (ft_strlen(str));
}

int	_lexer_find_match(char *symbols, char *input)
{
	int		token_length;
	char	*value;

	token_length = ft_strlen_sep(input, symbols);
	value = ft_substr(input, 0, token_length);
	if (symbols[0] == '"')
		_lexer_push_token(value, LEX_DOUBLE_QUOTES);
	else if (symbols[0] == '\'')
		_lexer_push_token(value, LEX_SINGLE_QUOTES);
	else
		_lexer_push_token(value, LEX_TERM);
	return (token_length);
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
			i += _lexer_push_token(ft_strdup("|"), LEX_PIPE);
		else if (!ft_strncmp(&ms()->input[i], "<<", 2))
			i += _lexer_push_token(ft_strdup("<<"), LEX_IN_2);
		else if (!ft_strncmp(&ms()->input[i], ">>", 2))
			i += _lexer_push_token(ft_strdup(">>"), LEX_OUT_2);
		else if (ms()->input[i] == '<')
			i += _lexer_push_token(ft_strdup("<"), LEX_IN_1);
		else if (ms()->input[i] == '>')
			i += _lexer_push_token(ft_strdup(">"), LEX_OUT_1);
		else if (ms()->input[i] == '"')
			i += _lexer_find_match("\"", &ms()->input[i + 1]) + 2;
		else if (ms()->input[i] == '\'')
			i += _lexer_find_match("'", &ms()->input[i + 1]) + 2;
		else
			i += _lexer_find_match(SYMBOLS, &ms()->input[i]);
	}
}
