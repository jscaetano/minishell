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

void	ft_cd()
{
	struct stat	stats;

	if (!ms()->tokens[1])
		return ;
	//same dir
	if (!ft_strcmp(ms()->tokens[1], "."))
		return ;
	stat(ms()->tokens[1], &stats);
	if (S_ISDIR(stats.st_mode))
	{
		chdir(ms()->tokens[1]);
		free(ms()->cwd);
		ms()->cwd = getcwd(NULL, 4096);
		return ;
	}
	else
		printf(CLR_RED"cd: no such file or directory: %s\n"CLR_RST, ms()->tokens[1]);
}
