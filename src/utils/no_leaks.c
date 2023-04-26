/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_leaks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:38:08 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/26 09:21:57 by ncarvalh         ###   ########.fr       */
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
	// ft_lstclear(&ms()->cmd_list, (void (*)(void *))ast_destroy_node);
	ast_clear(ms()->ast);
	matrix_destroy(ms()->pipes);
	matrix_destroy(ms()->tokens);
	ft_free(ms()->input);
	ms()->num_commands = 0;
	printf("\n");
	if (end)
	{
		ft_free(ms()->cwd);
		exit(EXIT_SUCCESS);
	}
}
