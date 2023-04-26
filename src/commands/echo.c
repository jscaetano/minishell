/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:33:06 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/26 16:15:24 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **tokens)
{
	int		i;

	if (!tokens[1])
		return ;
	i = 1;
	if (!ft_strcmp(tokens[1], "-n"))
		i++;
	if ((matrix_size(tokens) > 2 && !ft_strcmp(tokens[1], "-n")) \
		|| matrix_size(tokens) > 1)
	{
		while (tokens[i + 1])
		{
			printf("%s", tokens[i++]);
			printf(" ");
		}
		printf("%s", tokens[i++]);
	}
	if (ft_strcmp(tokens[1], "-n"))
		printf("\n");
}
