/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/07 20:00:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline(t_ast *node)
{
	if (!node)
		return ;
	execute_pipeline(node->left);
	execute_pipeline(node->right);
	if (node->token->type == LEX_TERM)
	{
		if (is_unforkable(node->args[0]))
			execute_command(node->args);
		else
			execute_forkable(node);
	}
	else if (node->token->type >= LEX_IN_1 && node->token->type <= LEX_OUT_2)
		execute_redirection(node->token->type, node->args[0]);
}

void	execute(t_ast *ast)
{
	int		status;

	status = 0;
	pipeline_create();
	execute_pipeline(ast);
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
		if (ms()->in_fd == -1 || ms()->out_fd == -1)
			sanitize(true);
		pipeline_apply(command->index);
		io_connect();
		execute_command(command->args);
		sanitize(true);			
	}
	io_disconnect(command->index);
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
		ft_env(args + 1);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args + 1);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(args + 1);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args + 1);
	else if (!ft_strcmp(args[0], "cd"))
		ft_cd(args + 1);
	else if (!ft_strcmp(args[0], "ptmp"))
		printtmp();
}

void	execute_if_exists(char *exe, char **argv)
{
	char	*path;

	path = get_executable_path(exe);
	if (path)
		execve(path, argv, ms()->envp);
	else
		error(ANSI_RED, ERROR_UNKNOWN_CMD, exe, 127);
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
