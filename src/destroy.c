/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:57:36 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/02/16 18:57:46 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
