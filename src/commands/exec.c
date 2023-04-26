/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/26 08:53:44 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *command)
{
	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "pwd") \
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "echo") \
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "export") \
		|| !ft_strcmp(command, "cd") || !ft_strcmp(command, "ptmp"));
}

void	execute_if_exists(char *exe, char **argv)
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
			execve(pathtoexe, argv, ms()->envv);
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
		execve(pathtoexe, argv, ms()->envv);
		free(pathtoexe);
		return ;
	}
	else if(access(exe, F_OK) == 0)
	{
		execve(pathtoexe, argv, ms()->envv);
		return ;
	}
	else
	{
		ms()->laststatus = 127;
		printf(CLR_RED"minishell: command not found: %s\n"CLR_RST, exe);
	}
	return ;
}

void	execute_command(char *command, char **args)
{
	if (!is_builtin(command))
		execute_if_exists(command, args);
	else if (!ft_strcmp(command, "exit"))
		no_leaks(1);
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

void	create_all_pipes()
{
	int	i;
	
	ms()->pipes = ft_calloc(ms()->num_commands, sizeof(int *));
	if (!ms()->pipes)
		return ;
	i = -1;
	while (++i < ms()->num_commands - 1)
	{
		ms()->pipes[i] = ft_calloc(2, sizeof(int));
		pipe(ms()->pipes[i]);
	}
}

void	connect_pipeline(int cmd_index)
{
	if (cmd_index >= 0 && cmd_index < ms()->num_commands - 1)
		dup2(ms()->pipes[cmd_index][WRITE_END], STDOUT_FILENO);
	if (cmd_index > 0 && cmd_index <= ms()->num_commands - 1)
		dup2(ms()->pipes[cmd_index - 1][READ_END], STDIN_FILENO);
}

bool	is_forkable(char *command)
{
	return (ft_strcmp(command, "cd") != 0 && ft_strcmp(command, "exit") != 0 \
		&& ft_strcmp(command, "export") != 0 && ft_strcmp(command, "unset") != 0 \
		&& ft_strcmp(command, "ptmp") != 0 );
}

void	execute_node(t_ast *command)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{	
		if (ms()->num_commands > 1)
		{
			connect_pipeline(command->index);
			if (ms()->pipes[command->index])
				close(ms()->pipes[command->index][READ_END]);
		}
		execute_command(command->args[0], command->args);
		exit(EXIT_SUCCESS);
	}
	if (ms()->pipes[command->index])
		close(ms()->pipes[command->index][WRITE_END]);
}

void	execute_command_list(t_list *cmd_list)
{
	t_ast	*command;
	
	create_all_pipes();
	while (cmd_list)
	{
		command = (t_ast *)cmd_list->content;
		if (is_forkable(command->args[0]))
			execute_node(command);
		else
			execute_command(command->args[0], command->args);			
		cmd_list = cmd_list->next;
	}	
	while (waitpid(0, NULL, 0) > 0);
	matrix_destroy(ms()->pipes);
}
