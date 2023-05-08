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

void	_change_dir(char *path)
{
	if (!ft_strcmp(path, ""))
		error(ANSI_RED, ERROR_CD_NO_HOME, NULL, 1);
	chdir(path);
	free(ms()->cwd);
	(ms()->cwd) = getcwd(NULL, 4096);
	free(path);
}

void	ft_cd(char **tokens)
{
	struct stat	stats;

	(ms()->exit_status) = 0;
	if (matrix_size(tokens) > 1)
	{
		error(ANSI_RED, ERROR_CD_MANY_ARGS, NULL, 1);
		return ;
	}
	if (!tokens[0] || !ft_strcmp(tokens[0], "~"))
	{
		_change_dir(get_env("HOME"));
		return ;
	}
	stat(tokens[0], &stats);
	if (S_ISDIR(stats.st_mode))
		_change_dir(ft_strdup(tokens[0]));
	else
		error(ANSI_RED, ERROR_CD_WRONG_DIR, tokens[0], 127);
}
