/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 12:45:03 by marvin            #+#    #+#             */
/*   Updated: 2023/05/07 12:45:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(char *term)
{
	char	*input;
	int		fd;
	int		n;
	int		pid;

	signals_heredoc();
	pid = fork();
	if (pid == 0)
	{
		fd = open(HEREDOC, O_WRONLY | O_CREAT | O_APPEND, 0600);
		while (1)
		{
			input = readline("heredoc > ");
			if (!input || !ft_strcmp(input, term))
				break ;
			n = ft_strlen(input);
			input[n] = '\n';
			if (write(fd, input, n + 1) == -1)
			{
				ft_free(input);
				close(fd);
				return (-1);
			}
			ft_free(input);
		}
		if (!input)
			printf("\n");
		close(fd);
		exit(0);
	}
	else
	{
		signals_2();
		waitpid(0, NULL, 0);
	}
	fd = open(HEREDOC, O_RDONLY);
	signals();
	return (fd);
}

void	execute_redirection(t_lexeme type, char *filename)
{
	if (type == LEX_OUT_1)
		(ms()->out_fd) = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (type == LEX_OUT_2)
		(ms()->out_fd) = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (type == LEX_IN_1)
		(ms()->in_fd) = open(filename, O_RDONLY);
	if (type == LEX_IN_2)
		(ms()->in_fd) = heredoc(filename);
	if (ms()->in_fd == -1 || ms()->out_fd == -1)
		error(ANSI_RED, ERROR_UNKNOWN_FILE, filename, 1);
}
