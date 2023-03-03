/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/03 19:35:24 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *pathtoexe, char **argv)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execve(pathtoexe, argv, ms()->envv);
	else
		waitpid(pid, NULL, 0);
}

void	exec_if_exists(char *exe, char **argv)
{
	char	*path;
	char	*pathtoexe;
	int		i;

	i = 0;
	while (ms()->path[i])
	{
		path = ft_strjoin(ms()->path[i], "/");
		pathtoexe = ft_strjoin(path, exe);
		free(path);
		if (access(pathtoexe, F_OK) == 0)
		{
			exec(pathtoexe, argv);
			free(pathtoexe);
			return ;
		}
		free(pathtoexe);
		i++;
	}
	path = ft_strjoin(ms()->cwd, "/");
	pathtoexe = ft_strjoin(path, exe);
	free(path);
	if (access(pathtoexe, F_OK) == 0)
	{
		exec(pathtoexe, argv);
		free(pathtoexe);
		return ;
	}
	else
		printf(CLR_RED"minishell: command not found: %s\n"CLR_RST, exe);
	return ;
}
