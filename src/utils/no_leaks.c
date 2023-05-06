/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_leaks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:38:08 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/06 18:29:37 by marvin           ###   ########.fr       */
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
	unlink(HEREDOC);
	ft_free(ms()->input);
	matrix_destroy(ms()->pipes);
	ft_lstclear(&ms()->lexemes, (void (*)(void *))token_destroy);
	ast_clear(ms()->ast);
	(ms()->pipes) = NULL;
	(ms()->num_commands) = 0;
	if (end)
	{
		ft_free(ms()->cwd);
		matrix_destroy(ms()->path);
		matrix_destroy(ms()->envp);
		exit(ms()->exit_status);
	}
}
