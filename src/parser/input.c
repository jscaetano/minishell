/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/06 20:47:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #ifdef DEBUG
// 	printf("\n\t -------- LEXER --------\n\n");
// 	lexer_debug();
// 	printf("\n\t --------- AST ---------\n\n");
// 	ast_debug(ms()->ast, 0, token_debug);
// #endif

void	update_envs(void)
{
	char	*tmp;
	
	matrix_destroy(ms()->path);
	matrix_destroy(ms()->envp);
	tmp = get_env("PATH");
	(ms()->path) = ft_split(tmp, ':');
	(ms()->envp) = envlist_to_matrix(ms()->envlist);
	free(tmp);
}

void	compute(void)
{
	if (is_spaces(ms()->input))
	{
		sanitize(false);
		return ;
	}
	lexer();
	expander();
	parser();
	if (!is_assignment(ms()->lexemes->content))
		execute(ms()->ast);
	update_envs();
	sanitize(false);
}

void	reader(void)
{
	signals();
	while (1)
	{
		(ms()->input) = readline(PROMPT);
		if (!ms()->input)
		{
			printf("exit\n");
			sanitize(true);
		}
		add_history(ms()->input);
		compute();
	}
	rl_clear_history();
}
