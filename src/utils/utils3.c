/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:50:12 by crypto            #+#    #+#             */
/*   Updated: 2023/04/08 11:24:18 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	matrix_destroy(void *matrix)
{
	size_t i;

	if (!matrix)
		return ;
	i = 0;
	while (((char**)matrix)[i])
		free(((char**)matrix)[i++]);
	free(matrix);
}

int	is_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\f' && str[i] != '\n'
		&& str[i] != '\r' && str[i] != '\t'
		&& str[i] != '\v' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
