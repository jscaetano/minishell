/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 16:12:35 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/05/06 18:20:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_all_pipes(void)
{
	int	i;

	(ms()->pipes) = ft_calloc(ms()->num_commands, sizeof(int *));
	if (!ms()->pipes)
		return ;
	i = -1;
	while (++i < ms()->num_commands - 1)
	{
		(ms()->pipes[i]) = ft_calloc(2, sizeof(int));
		pipe(ms()->pipes[i]);
	}
}

void	connect_pipeline(int cmd_index)
{
	if (ms()->num_commands < 2)
		return ;
	if (ms()->in_fd == STDIN_FILENO)
		if (cmd_index != 0)
			ms()->in_fd = ms()->pipes[cmd_index - 1][READ_END];
	if (ms()->out_fd == STDOUT_FILENO)
		if (cmd_index != ms()->num_commands - 1)
			ms()->out_fd = ms()->pipes[cmd_index][WRITE_END];
	if (ms()->pipes[cmd_index])
		close(ms()->pipes[cmd_index][READ_END]);
}

void	connect_io(void)
{
	dup2(ms()->in_fd, STDIN_FILENO);
	dup2(ms()->out_fd, STDOUT_FILENO);
}

bool	is_unforkable(char *command)
{
	return (!ft_strcmp(command, "cd") || !ft_strcmp(command, "exit") \
		|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset") \
		|| !ft_strcmp(command, "ptmp"));
}

bool	is_builtin(char *command)
{
	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "pwd") \
		|| !ft_strcmp(command, "env") || !ft_strcmp(command, "echo") \
		|| !ft_strcmp(command, "unset") || !ft_strcmp(command, "export") \
		|| !ft_strcmp(command, "cd") || !ft_strcmp(command, "ptmp"));
}
