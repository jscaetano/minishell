/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/25 14:28:46 by marvin           ###   ########.fr       */
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
	exit(EXIT_SUCCESS);	
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

void	close_all_pipes()
{
	int i;

	i = -1;
	while (++i < ms()->num_commands - 1)
	{
		close(ms()->pipes[i][READ_END]);
		close(ms()->pipes[i][WRITE_END]);
	}	
}

void	first_pipeline_command(int node_index)
{
	printf("First command index [%d] - Input [-] Output [%d]\n", node_index, ms()->pipes[node_index][WRITE_END]);
	dup2(ms()->pipes[node_index][WRITE_END], STDOUT_FILENO);
}

void	last_pipeline_command(int node_index)
{
	printf("Last command index [%d] - Input [%d] - Output [-]\n", node_index, ms()->pipes[node_index - 1][READ_END]);
	dup2(ms()->pipes[node_index - 1][READ_END], STDIN_FILENO);
}

void	middle_pipeline_command(int node_index)
{
	printf("command index [%d] - Input [%d] - Output [%d]\n", node_index, ms()->pipes[node_index - 1][READ_END], ms()->pipes[node_index][WRITE_END]);
	dup2(ms()->pipes[node_index - 1][READ_END], STDIN_FILENO);
	dup2(ms()->pipes[node_index][WRITE_END], STDOUT_FILENO);
}

void	execute_node(t_ast *node)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{	
		if (ms()->num_commands == 1)
			execute_command(node->args[0], node->args);			
		else if (node->index == 0)
			first_pipeline_command(node->index);
		else if (node->index == ms()->num_commands - 1)
			last_pipeline_command(node->index);
		else
			middle_pipeline_command(node->index);
		close_all_pipes();
		execute_command(node->args[0], node->args);
	}
	waitpid(-1, NULL, 0);
	// printf("pid: %d command: %s\n", pid, node->args[0]);
}

void	execute_command_list(t_list *cmd_list)
{
	t_ast	*command;
	
	command = (t_ast *)cmd_list->content;
	create_all_pipes();
	while (cmd_list)
	{
		command = (t_ast *)cmd_list->content;
		execute_node(command);
		wait(NULL);
		cmd_list = cmd_list->next;
	}
	close_all_pipes();
	matrix_destroy(ms()->pipes);
}
