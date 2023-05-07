/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/07 20:32:40 by marvin           ###   ########.fr       */
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

char	*_update_prompt(void)
{
	char	*tmp;
	char	*prompt;
	char	*prefix;
	char	*suffix;

	prefix = ANSI_BOLD""PROMPT_UPPER""ANSI_UNDERLINE""ANSI_LCYAN;
	suffix = ANSI_RST"\n"ANSI_WHITE""PROMPT_LOWER""ANSI_RST;
	tmp = ft_strjoin(prefix, ms()->cwd);
	prompt = ft_strjoin(tmp, suffix);
	free(tmp);
	return (prompt);
}


void	_compute(void)
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
		ms()->prompt = _update_prompt();
		(ms()->input) = readline(ms()->prompt);
		if (!ms()->input)
		{
			printf("exit\n");
			sanitize(true);
		}
		add_history(ms()->input);
		_compute();
	}
	rl_clear_history();
}
