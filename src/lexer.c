/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:10:46 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/03/04 19:34:27 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	new_lexer(int n)
{
	t_lexer lexer;

	lexer.head = 0;
	lexer.n = n;
	return (lexer);
}

t_token	*new_token(char *str, t_lexeme type)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*get_last_token(t_lexer *lexer)
{
	t_token	*aux;

	if (!lexer || !lexer->head)
		return (NULL);
	aux = lexer->head;
	while (aux->next)
		aux = aux->next;
	return (aux);
}

/* Pass minishell struct, create a new token struct and add it to the token list */
void	add_token(t_ms *ms, char *str, t_lexeme lexeme)
{
	t_token	*token;

	token = new_token(str, lexeme);
	if (!token || !str)
		no_leaks(1);
	if (!ms->lexer.head)
		ms->lexer.head = token;
	else
		get_last_token(&ms->lexer)->next = token;
	ms->lexer.n++;
}

// To remove the tokens after each input
void	clean_lexer_tokens(t_lexer *lexer)
{
	(void)lexer;
	return ;
}

//cat filename | grep Error | sort >> "asfasf afasfasf"
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
		{
			printf("space ");
			token_length = 1;
		}
		else if (ms->input[i] == '|')
		{
			add_token(ms, ft_strdup("|"), LEX_PIPE);
			token_length = 1;
		}
		else if (ms->input[i] == '<')
		{
			token_length = 1;
			if (ms->input[i + 1] == '<')
			{
				add_token(ms, ft_strdup("<<"), LEX_IN_REDIR_2);
				token_length++;
			}
			else
				add_token(ms, ft_strdup("<"), LEX_IN_REDIR_1);
		}
		else if (ms->input[i] == '>')
		{
			token_length = 1;
			if (ms->input[i + 1] == '>')
			{
				add_token(ms, ft_strdup(">>"), LEX_OUT_REDIR_2);
				token_length++;
			}
			else
				add_token(ms, ft_strdup(">"), LEX_OUT_REDIR_1);
		}
		else if (ms->input[i] == '"')
		{
			token_length = ft_strlen_delim(&ms->input[i + 1], '\"', 0) + 2;
			add_token(ms, ft_substr(&ms->input[i], 0, token_length), LEX_DOUBLE_QUOTES);
		}
		else if (ms->input[i] == '\'')
		{
			token_length = ft_strlen_delim(&ms->input[i + 1], '\'', 0) + 2;
			add_token(ms, ft_substr(&ms->input[i], 0, token_length), LEX_SINGLE_QUOTES);
		}
		else
		{
			printf("term ");
			token_length = ft_strlen_delim(&ms->input[i], 0, 1);
			add_token(ms, ft_substr(&ms->input[i], 0, token_length), LEX_TERM);
		}
		i += token_length;
		#ifdef DEBUG
			//printf("tokenlen = %d\n", token_length);
			//printf("i = %d\n", i);
			sleep(1);
		#endif
	}
}

/* void	lexer2(t_ms *ms)
{
	int	i;
	int	len;
	int	token_len;

	i = 0;
	len = ft_strlen(ms->input);
	while (i < len)
	{
		token_len = ft_strlen_delim(ms->input, SYMBOLS);

	}
} */
