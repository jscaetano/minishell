/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/12 14:13:19 by ncarvalh         ###   ########.fr       */
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
		printf(CLR_RED"minishell: command not found: %s\n"CLR_RST, exe);
	return ;
}

void	exec_builtin(t_ast **node)
{
	if (!ft_strcmp((*node)->args[0], "exit"))
		no_leaks(1);
	else if (!ft_strcmp((*node)->args[0], "pwd"))
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp((*node)->args[0], "env"))
		ft_env();
	else if (!ft_strcmp((*node)->args[0], "echo"))
		ft_echo((*node)->args);
	else if (!ft_strcmp((*node)->args[0], "unset"))
		ft_unset((*node)->args);
	else if (!ft_strcmp((*node)->args[0], "export"))
		ft_export((*node)->args);
	else if (!ft_strcmp((*node)->args[0], "cd"))
		ft_cd((*node)->args);
	else if (!ft_strcmp((*node)->args[0], "ptmp"))
		printtmp();	
}

bool	is_builtin(char *command)
{
	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "pwd") \
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "echo") \
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "export") \
		|| !ft_strcmp(command, "cd") || !ft_strcmp(command, "ptmp"));
}

void	exec_node(t_ast **node)
{
	if ((*node)->token->type != LEX_TERM)
		return ;
	if (is_builtin((*node)->args[0]))
		exec_builtin(node);
	else
		exec_if_exists((*node)->args[0], (*node)->args);	
}
