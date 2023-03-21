/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:50:12 by crypto            #+#    #+#             */
/*   Updated: 2023/03/21 19:11:06 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    matrix_destroy(void *matrix)
{
    size_t i;

	if (!matrix)
		return ;
    i = 0;
    while (((char**)matrix)[i])
        free(((char**)matrix)[i++]);
    free(matrix);
}