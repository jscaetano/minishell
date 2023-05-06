/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:33:06 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/06 19:35:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **tokens)
{
	int		i;

	if (!tokens[0])
		return ;
	i = 0;
	ms()->exit_status = 0;
	if (!ft_strcmp(tokens[0], "-n"))
		i++;
	if ((matrix_size(tokens) > 1 && !ft_strcmp(tokens[0], "-n")) \
		|| matrix_size(tokens) > 0)
	{
		while (tokens[i + 1])
		{
			printf("%s", tokens[i++]);
			printf(" ");
		}
		printf("%s", tokens[i++]);
	}
	if (ft_strcmp(tokens[0], "-n") != 0)
		printf("\n");
}
