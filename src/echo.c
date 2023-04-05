/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:33:06 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/05 12:05:11 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(void)
{
	int		i;

	i = 1;
	if (!ft_strcmp(ms()->tokens[1], "-n"))
		i++;
	while (ms()->tokens[i + 1])
	{
		printf("%s", ms()->tokens[i++]);
		printf(" ");
	}
	printf("%s", ms()->tokens[i++]);
	if (ft_strcmp(ms()->tokens[1], "-n"))
		printf("\n");
}
