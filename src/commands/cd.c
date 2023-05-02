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

void	change_dir(char *path)
{
	chdir(path);
	free(ms()->cwd);
	ms()->cwd = path;
}

void	ft_cd(char **tokens)
{
	struct stat	stats;

	(ms()->exit_status) = 0;
	if (matrix_size(tokens) > 1)
	{
		(ms()->exit_status) = 1;
		message(CLR_RED, ERROR_EXIT_MANY_ARGS, NULL);
		return ;
	}
	if (!tokens[0] || !ft_strcmp(tokens[0], "~"))
	{
		change_dir(get_env("HOME"));
		return ;
	}
	if (!ft_strcmp(tokens[0], "."))
		return ;
	stat(tokens[0], &stats);
	if (S_ISDIR(stats.st_mode))
		change_dir(tokens[0]);
	else
	{
		(ms()->exit_status) = 127;
		message(CLR_RED, ERROR_UNKNOWN_DIR, tokens[0]);
	}
}