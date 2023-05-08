/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/08 09:58:15 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// #ifdef DEBUG
// 	printf("\n\t -------- LEXER --------\n\n");
// 	lexer_debug();
// 	printf("\n\t --------- AST ---------\n\n");
// 	ast_debug(ms()->ast, 0, token_debug);
// #endif

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

int	_compute(void)
{
	if (is_spaces(ms()->input))
		return (0);
	lexer();
	if (!lexical_analysis())
		return (0);
	expander();
	parser();
	if (!is_assignment(ms()->lexemes->content))
		execute(ms()->ast);
	update_envs();
	return (0);
}

void	reader(void)
{	
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
		sanitize(false);
	}
	rl_clear_history();
}
