/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crypto <crypto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:50:12 by crypto            #+#    #+#             */
/*   Updated: 2023/03/17 16:55:08 by crypto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    matrix_destroy(void *matrix)
{
    size_t i;

    i = 0;
    while (((char**)matrix)[i])
        free(((char**)matrix)[i++]);
    free(matrix);
}