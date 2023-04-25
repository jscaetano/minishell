/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/25 15:57:30 by marvin           ###   ########.fr       */
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

void	close_all_pipes(int node_index, int end)
{
	int i;
	
	if (!ms()->pipes[node_index])
		return ;

	i = -1;
	while (++i <= node_index)
		close(ms()->pipes[i][end]);
}

void	first_pipeline_command(int node_index)
{
	#ifdef DEBUG
		printf("First -> Input [-][-] Output [%d][WRITE_END]\n", node_index);
	#endif
	dup2(ms()->pipes[node_index][WRITE_END], STDOUT_FILENO);
}

void	last_pipeline_command(int node_index)
{
	#ifdef DEBUG
		printf("Last -> Input [%d][READ_END] Output [-][-]\n", node_index - 1);
	#endif
	dup2(ms()->pipes[node_index - 1][READ_END], STDIN_FILENO);
}

void	middle_pipeline_command(int node_index)
{
	#ifdef DEBUG
		printf("Input [%d][READ_END] - Output [%d][WRITE_END]\n", node_index - 1, node_index);
	#endif
	dup2(ms()->pipes[node_index][WRITE_END], STDOUT_FILENO);
	dup2(ms()->pipes[node_index - 1][READ_END], STDIN_FILENO);
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
		close_all_pipes(node->index, READ_END);
		execute_command(node->args[0], node->args);
	}
	close_all_pipes(node->index, WRITE_END);
}

void	execute_command_list(t_list *cmd_list)
{
	t_ast	*command;
	
	create_all_pipes();
	while (cmd_list)
	{
		command = (t_ast *)cmd_list->content;
		execute_node(command);
		cmd_list = cmd_list->next;
	}	
	while (1)
	{
		int pid;
		pid = waitpid(0, NULL, 0);
		printf("Waited for: %d\n", pid);
		if (pid <= 0)
			break;
	}
	matrix_destroy(ms()->pipes);
}
