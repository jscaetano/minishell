/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:10:46 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/05/08 21:18:37 by ncarvalh         ###   ########.fr       */
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
		}
		scanner(NEXT);
	}
	if (num_pipes >= num_commands)
		return (error(ANSI_RED, ERROR_UNCLOSED_PIPES, NULL, 2));
	return (true);
}

bool	remove_if(t_token *token, t_token *to_remove)
{
	return (ft_strcmp(token->str, to_remove->str) == 0);
}

void	lexer_join(t_list *lexemes)
{
	t_list	*curr;
	t_token *token;
	char	*tmp;

	curr = lexemes;
	while (curr)
	{
		token = curr->content;
		if (!curr->next)
			return ;
		if (!token->is_joinable)
		{
			curr = curr->next;
			continue ;
		}
		tmp = token->str;
		token->str = ft_strjoin(token->str, \
			((t_token *)curr->next->content)->str);
		ft_list_remove_if(&ms()->lexemes, curr->next->content, remove_if, token_destroy);
		free(tmp);
	}
}

int	_lexer_push_token(char *str, t_lexeme lexeme, bool is_joinable)
{
	t_token	*token;

	token = token_new(str, lexeme, is_joinable);
	if (!token || !str)
		return (0);
	ft_lstadd_back(&ms()->lexemes, ft_lstnew(token));
	return (ft_strlen(str));
}

int	_lexer_find_match(char *symbols, char *input)
{
	char	*value;
	int		tk_len;
	bool	is_joinable;

	is_joinable = false;
	tk_len = ft_strlen_sep(input, symbols);
	// #ifdef DEBUG
	// 	printf("\n\t---------------------------\n\n");
	// 	printf("input: %s\n", input);
	// 	printf("input[%d]: '%c'\n", tk_len, input[tk_len]);
	// #endif
	if (input[tk_len])
		if (input[tk_len + 1] != ' ' && ft_strchr("\'\"", input[tk_len]))
			is_joinable = true;
	// #ifdef DEBUG
	// 	printf("is_joinable: %d\n", is_joinable);
	// #endif
	value = ft_substr(input, 0, tk_len);
	if (symbols[0] == '"')
		_lexer_push_token(value, LEX_DOUBLE_QUOTES, is_joinable);
	else if (symbols[0] == '\'')
		_lexer_push_token(value, LEX_SINGLE_QUOTES, is_joinable);
	else
		_lexer_push_token(value, LEX_TERM, is_joinable);		
	return (tk_len);
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
	lexer_join(ms()->lexemes);
}
