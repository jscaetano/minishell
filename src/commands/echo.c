/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:33:06 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/07 12:33:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **tokens)
{
	int		i;

	i = 0;
	ms()->exit_status = 0;
	if (tokens[0] && !ft_strcmp(tokens[0], "-n"))
		i++;
	while (tokens[i])
	{
		printf("%s", tokens[i++]);
		if (tokens[i])
			printf(" ");
	}
	if (!tokens[0] || ft_strcmp(tokens[0], "-n") != 0)
		printf("\n");
}
