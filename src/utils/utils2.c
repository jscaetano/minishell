/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:37:44 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/06 20:12:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	matrix_destroy(void *matrix)
{
	size_t	i;
	char	**mat;

	if (!matrix)
		return ;
	i = 0;
	mat = (char **)matrix;
	while (mat[i])
		free(mat[i++]);
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

size_t	matrix_size(char **mat)
{
	size_t	i;

	if (!mat)
		return (0);
	i = 0;
	while (mat[i])
		i++;
	return (i);
}

char	**matrix_append(char **m1, char *str)
{
	char	**res;
	size_t	i;

	i = -1;
	res = ft_calloc(matrix_size(m1) + 2, sizeof(char *));
	if (!res)
		return (NULL);
	while (m1[++i])
		res[i] = ft_strdup(m1[i]);
	res[i] = str;
	matrix_destroy(m1);
	return (res);
}

void	error(char *color, char *message, char *param, int status)
{
	if (param)
		printf("%s%s%s%s\n", color, message, param, CLR_RST);
	else
		printf("%s%s%s\n", color, message, CLR_RST);
	(ms()->exit_status) = status;
}
