/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:33:06 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/03 19:33:15 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(int flag)
{
	int		i;
	int		size;
	char	*tmp;

	size = 0;
	i = 1;
	if (flag)
		i++;
	while (ms()->tokens[i])
	{
		if (ms()->tokens[i][0] == '$')
		{
			if (ft_strlen(ms()->tokens[i]) != 1)
			{
				if (get_env(ms()->tokens[i]))
				{
					size = ft_strlen(get_env(ms()->tokens[i]));
					tmp = malloc(sizeof(char) * (size + 1));
					tmp = get_env(ms()->tokens[i]);
					ft_free(ms()->tokens[i]);
					ms()->tokens[i] = malloc(sizeof(char) * (size));
					ms()->tokens[i] = tmp;
				}
				else
					ms()->tokens[i] = "";
			}
		}
		printf("%s", ms()->tokens[i++]);
		if (!flag)
			printf("\n");
	}
}
