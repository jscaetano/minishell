/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:24:50 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/02 19:41:07 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd()
{
	struct stat	stats;

	if (!g_ms.tokens[1])
		return ;
	//same dir
	if (!ft_strcmp(g_ms.tokens[1], "."))
		return ;
	stat(g_ms.tokens[1], &stats);
	if (S_ISDIR(stats.st_mode))
	{
		chdir(g_ms.tokens[1]);
		g_ms.cwd = getcwd(NULL, 4096);
		return ;
	}
	else
		printf("cd: no such file or directory: %s\n", g_ms.tokens[1]);
}
