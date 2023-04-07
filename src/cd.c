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

void	ft_cd(char **tokens)
{
	struct stat	stats;
	char		*cwd;

	if (!tokens[1])
		return ;
	if (!ft_strcmp(tokens[1], "."))
		return ;
	stat(tokens[1], &stats);
	if (S_ISDIR(stats.st_mode))
	{
		chdir(tokens[1]);
		free(ms()->cwd);
		cwd = getcwd(NULL, 4096);
		ms()->cwd = cwd;
		return ;
	}
	else
		printf(CLR_RED"cd: no such file or directory: %s\n"CLR_RST, \
			tokens[1]);
}
