/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/02 19:01:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			execute_forkable(command);
		cmd_list = cmd_list->next;
	}
	while (waitpid(0, &status, 0) > 0)
		continue ;
	signals();
	if (WIFEXITED(status))
		ms()->exit_status = WEXITSTATUS(status);
}

void	execute_forkable(t_ast *command)
{
	pid_t	pid;

	signals_child();
	pid = fork();
	if (pid == 0)
	{
		if (ms()->num_commands > 1)
			connect_pipeline(command->index);
		execute_command(command->args);
		exit(ms()->exit_status);
	}
	if (ms()->pipes[command->index])
		close(ms()->pipes[command->index][WRITE_END]);
}

void	execute_command(char **args)
{
	if (!is_builtin(args[0]))
		execute_if_exists(args[0], args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args + 1);
	else if (!ft_strcmp(args[0], "pwd"))
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(args[0], "env"))
		ft_env();
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(args + 1);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args + 1);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(args);
	else if (!ft_strcmp(args[0], "ptmp"))
		printtmp();
}

void	execute_if_exists(char *exe, char **argv)
{
	char	*path;

	path = get_executable_path(exe);
	if (path)
		execve(path, argv, ms()->envv);
	(ms()->exit_status) = EXIT_UNKNOWN_COMMAND;
	message(CLR_RED, ERROR_UNKNOWN_CMD, exe);
	free(path);
	return ;
}

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
