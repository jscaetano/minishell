/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 17:35:01 by marvin            #+#    #+#             */
/*   Updated: 2023/03/17 17:35:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token*    scanner(t_scanner_op op)
{
    static t_token  *current = NULL;

	if (!current)
		current = ms()->lexer.head;
    if (op == NEXT)
		current = current->next;
    else if (op == RESET)
        current = NULL;
    return (current);
}