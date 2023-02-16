/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:10:46 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/02/16 18:53:55 by ncarvalh         ###   ########.fr       */
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

void	destroy_token(t_token *token)
{
	free(token->str);
	free(token);
}

void	destroy_lexer(t_lexer *lexer)
{
	t_token	*aux;
	t_token	*curr;

	curr = lexer->head;
	while (curr != NULL)
	{
		aux = curr->next;
		destroy_token(curr);
		curr = aux;		
	}	
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

void	print_token(t_token *token)
{
	if (token->type == LEX_IN_REDIR_1)
		printf("[ LEX_IN_REDIR_1 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_REDIR_1)
		printf("[ LEX_OUT_REDIR_1 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_IN_REDIR_2)
		printf("[ LEX_IN_REDIR_2 ] -> \"%s\"\n", token->str);
	else if (token->type == LEX_OUT_REDIR_2)
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

void	print_lexer(t_lexer *lexer)
{	
	int		i;
	t_token	*token;
	
	i = 1;
	token = lexer->head;
	while (token)
	{	
		printf("[%2d]", i++);
		print_token(token);
		token = token->next;
	}
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
		token_length = ft_strclen(&ms->input[i], ' ');
		if (ms->input[i] == ' ')
			i++;
		else if (!ft_strncmp(&ms->input[i], "|", 1) && token_length == 1)
			add_token(ms, ft_strdup("|"), LEX_PIPE);
		else if (!ft_strncmp(&ms->input[i], "<", 1) && token_length == 1)
			add_token(ms, ft_strdup("<"), LEX_IN_REDIR_1);
		else if (!ft_strncmp(&ms->input[i], ">", 1) && token_length == 1)
			add_token(ms, ft_strdup(">"), LEX_OUT_REDIR_1);
		else if (!ft_strncmp(&ms->input[i], "<<", 2) && token_length == 2)
			add_token(ms, ft_strdup("<<"), LEX_IN_REDIR_2);
		else if (!ft_strncmp(&ms->input[i], ">>", 2) && token_length == 2)
			add_token(ms, ft_strdup(">>"), LEX_OUT_REDIR_2);
		else if (!ft_strncmp(&ms->input[i], "\"", 1))
		{
			token_length = ft_strclen(&ms->input[i + 1], '"') + 2;
			add_token(ms, ft_substr(&ms->input[i + 1], 0, token_length - 2), LEX_DOUBLE_QUOTES);
		}
		else if (!ft_strncmp(&ms->input[i], "'", 1))
		{
			token_length = ft_strclen(&ms->input[i + 1], '\'') + 2;
			add_token(ms, ft_substr(&ms->input[i + 1], 0, token_length - 2), LEX_SINGLE_QUOTES);
		}
		else
			add_token(ms, ft_substr(&ms->input[i], 0, token_length), LEX_TERM);
		i += token_length;
	}
}