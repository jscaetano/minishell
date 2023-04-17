/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/17 10:54:20 by ncarvalh         ###   ########.fr       */
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
		printf(CLR_RED"minishell: command not found: %s\n"CLR_RST, exe);
	return ;
}

void	exec_command(char *command, char **args)
{
	if (!is_builtin(command))
		exec_if_exists(command, args);
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

void	exec_node(t_ast *node)
{
	pid_t	pid;
	int		status;

	status = 0;
	pipe(ms()->inpipe);
	pid = fork();
	if (pid == 0)
	{
		if (node->index != ms()->num_commands - 1)
		{
			close(ms()->inpipe[READ_END]);
			dup2(ms()->inpipe[WRITE_END], STDOUT_FILENO);			
		}
		exec_command(node->args[0], node->args);			
	}
	else
		waitpid(pid, &status, 0);
	if (ms()->num_commands > 1)
	{
		close(ms()->inpipe[WRITE_END]);
		dup2(ms()->inpipe[READ_END], STDIN_FILENO);
	}
	close(ms()->inpipe[READ_END]);
	close(ms()->inpipe[WRITE_END]);
	ms()->laststatus = WEXITSTATUS(status);
}

void	exec_pipeline(t_ast *node)
{
	if (node->token->type == LEX_TERM)
		exec_node(node);
	else if (node->token->type == LEX_PIPE)
	{
		exec_pipeline(node->left);
		exec_pipeline(node->right);
	}
}
