/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crypto <crypto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/27 18:04:17 by crypto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_executable_path(char *exe)
{
	char	*tmp;
	char	*path;
	int		i;

	i = -1;
	while (ms()->path[++i])
	{
		tmp = ft_strjoin(ms()->path[i], "/");
		path = ft_strjoin(tmp, exe);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	tmp = ft_strjoin(ms()->cwd, "/");
	path = ft_strjoin(tmp, exe);
	free(tmp);
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	if (access(exe, F_OK) == 0)
		return (ft_strdup(exe));
	return (NULL);
}

void	execute_if_exists(char *exe, char **argv)
{
	char	*path;

	path = get_executable_path(exe);
	if (path)
		execve(path, argv, ms()->envv);
	else
	{
		(ms()->laststatus) = 127;
		message(CLR_RED, ERROR_UNKNOWN_CMD, exe);
	}
	free(path);
	return ;
}
/* 
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
} */

void	execute_command(char **args)
{
	char	*command;

	command = args[0];
	if (!is_builtin(command))
		execute_if_exists(command, args);
	else if (!ft_strcmp(command, "exit"))
		sanitize(true);
	else if (!ft_strcmp(command, "pwd"))
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(command, "env"))
		ft_env();
	else if (!ft_strcmp(command, "echo"))
		ft_echo(args);
	else if (!ft_strcmp(command, "unset"))
		ft_unset(args);
	else if (!ft_strcmp(command, "export"))
		ft_export(args);
	else if (!ft_strcmp(command, "cd"))
		ft_cd(args);
	else if (!ft_strcmp(command, "ptmp"))
		printtmp();
}

void	execute_node(t_ast *command)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{	
		if (ms()->num_commands > 1)
			connect_pipeline(command->index);
		execute_command(command->args);
		exit(EXIT_SUCCESS);
	}
	if (ms()->pipes[command->index])
		close(ms()->pipes[command->index][WRITE_END]);
}

void	execute_command_list(t_list *cmd_list)
{
	t_ast	*command;
	int		status;

	create_all_pipes();
	while (cmd_list)
	{
		command = (t_ast *)cmd_list->content;
		if (is_unforkable(command->args[0]))
			execute_command(command->args);
		else
			execute_node(command);
		cmd_list = cmd_list->next;
	}	
	while (waitpid(0, &status, 0) > 0)
		continue ;
}
