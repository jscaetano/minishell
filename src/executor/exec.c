/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:24:58 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/08 21:16:45 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_execute_if_exists(char *exe, char **argv)
{
	char	*path;

	path = get_executable_path(exe);
	if (path)
	{
		execve(path, argv, ms()->envp);
		error(ANSI_RED, ERROR_NO_PERMISSIONS, exe, 126);
	}
	else
		error(ANSI_RED, ERROR_UNKNOWN_CMD, exe, 127);
	free(path);
	return ;
}

void	_execute_command(char **args)
{
	(ms()->exit_status) = 0;
	if (!is_builtin(args[0]))
		_execute_if_exists(args[0], args);
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
		tmp_debug();
}

pid_t	_execute_forkable(t_ast *command)
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
		_execute_command(command->args);
		sanitize(true);
	}
	io_disconnect(command->index);
	return (pid);
}

pid_t	_execute_pipeline(t_ast *node)
{
	pid_t	last;

	last = 0;
	if (!node)
		return (last);
	last = _execute_pipeline(node->left);
	last = _execute_pipeline(node->right);
	if (node->token->type == LEX_TERM ||
		node->token->type == LEX_DOUBLE_QUOTES ||
		node->token->type == LEX_SINGLE_QUOTES)
	{
		if (is_unforkable(node->args[0]))
			_execute_command(node->args);
		else
			last = _execute_forkable(node);
	}
	else if (node->token->type >= LEX_IN_1 && node->token->type <= LEX_OUT_2)
		execute_redirection(node->token->type, node->args[0]);
	return (last);
}

void	execute(t_ast *ast)
{
	int		status;
	pid_t	last;

	status = 0x7F;
	pipeline_create();
	last = _execute_pipeline(ast);
	last = waitpid(last, &status, 0);
	while (waitpid(0, NULL, 0) > 0)
		continue ;
	if (WIFEXITED(status))
		ms()->exit_status = WEXITSTATUS(status);
	signals();
}
