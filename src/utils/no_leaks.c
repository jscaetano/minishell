/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_leaks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:38:08 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/06 17:40:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *p)
{
	if (p)
		free(p);
	p = NULL;
}

void	sanitize(bool end)
{
	ft_lstclear(&ms()->lexemes, (void (*)(void *))token_destroy);
	ast_clear(ms()->ast);
	matrix_destroy(ms()->pipes);
	ft_free(ms()->input);
	matrix_destroy(ms()->envp);
	(ms()->envp) = envlist_to_matrix(ms()->envlist);
	(ms()->pipes) = NULL;
	(ms()->num_commands) = 0;
	unlink(HEREDOC);
	if (end)
	{
		ft_free(ms()->cwd);
		printf("Exit status: %d\n", ms()->exit_status);
		exit(ms()->exit_status);
	}
}
