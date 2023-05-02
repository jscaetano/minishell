/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_leaks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:38:08 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/02 19:26:27 by marvin           ###   ########.fr       */
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
	ft_lstclear(&ms()->cmd_list, (void (*)(void *))ast_clear);
	ast_clear(ms()->ast);
	matrix_destroy(ms()->pipes);
	ft_free(ms()->input);
	ms()->pipes = NULL;
	ms()->num_commands = 0;
	if (end)
	{
		ft_free(ms()->cwd);
		printf("Exit status: %d\n", ms()->exit_status);
		exit(ms()->exit_status);
	}
}
