/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 18:35:27 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/16 18:35:27 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *pathtoexe, char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execve(pathtoexe, argv, ms()->envv);
	else
	{
		waitpid(pid, &status, 0);
		ms()->laststatus = WEXITSTATUS(status);
	}
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
	else if(access(exe, F_OK) == 0)
	{
		exec(exe, argv);
		return ;
	}
	else
	{
		ms()->laststatus = 127;
		printf(CLR_RED"minishell: command not found: %s\n"CLR_RST, exe);
	}
	return ;
}
