/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_leaks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:38:08 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/03 19:38:41 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *p)
{
	if (p)
		free(p);
}

void	no_leaks(int end)
{
	int	i;

	i = 0;
	ft_free(ms()->input);
	if (!ms()->tokensfreed)
	{
		while (ms()->tokens[i])
			ft_free(ms()->tokens[i++]);
		ft_free(ms()->tokens);
		ms()->tokensfreed = 1;
	}
	printf("\n");
	if (end)
	{
		ft_free(ms()->cwd);
		exit(EXIT_SUCCESS);
	}
}
