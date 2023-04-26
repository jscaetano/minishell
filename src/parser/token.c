/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:40:47 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/04/26 11:43:08 by ncarvalh         ###   ########.fr       */
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

t_token	*token_copy(t_token *token)
{
	t_token	*dup;

	dup = token_new(ft_strdup(token->str), token->type);
	if (!dup)
		return (NULL);
	return (dup);
}

void	token_destroy(void *token)
{
	if (!token)
		return ;
	ft_free(((t_token *)token)->str);
	ft_free(token);
}