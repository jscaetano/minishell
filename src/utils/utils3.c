/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:50:12 by crypto            #+#    #+#             */
/*   Updated: 2023/04/17 10:41:36 by ncarvalh         ###   ########.fr       */
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

char	**matrix_copy(char **matrix)
{
	char	**dup;
	size_t	i;

	i = 0;
	while (matrix[i])
		i++;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	i = -1;
	while (matrix[++i])
		dup[i] = ft_strdup(matrix[i]);
	return (dup);
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
