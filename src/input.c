/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/21 17:20:00 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_args(void)
{
	t_list	*node;
	t_token	*token;

	node = ms()->lexemes;
	while (node)
	{
		token = (t_token *)node->content;
		token->args = ft_split(token->str, ' ');
		node = node->next;
	}
	return ;
}

void	handle_input(void)
{
	char	**tokens;

	lexer(ms());
	token_args();
	// print_lexer_args();
	ms()->ast = parser();
	#ifdef DEBUG
		ast_print(ms()->ast, 0, &token_print);
		printf("\n\n\n\n");
	#endif
	tokens = ft_split(ms()->input, ' ');
	ms()->tokens = tokens;
	ms()->tokensfreed = 0;
	if (find_equals())
		return ;
	if (!ft_strcmp(ms()->tokens[0], "exit"))
		no_leaks(1);
	else if (!ft_strcmp(ms()->tokens[0], "pwd"))
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(ms()->tokens[0], "env"))
		ft_env();
	else if (!ft_strcmp(ms()->tokens[0], "echo"))
	{
		if (ms()->tokens[1])
		{
			if (!ft_strcmp(ms()->tokens[1], "-n"))
				ft_echo(1);
			else
				ft_echo(0);
		}
	}
	else if (!ft_strcmp(ms()->tokens[0], "unset"))
		ft_unset();
	else if (!ft_strcmp(ms()->tokens[0], "export"))
		ft_export();
	else if (!ft_strcmp(ms()->tokens[0], "cd"))
		ft_cd();
	else if ((!ft_strcmp(ms()->tokens[0], "ptmp")))
		printtmp();
	else
		exec_if_exists(ms()->tokens[0], NULL);
	ast_traverse(ms()->ast, &ast_destroy_node);
}

void	read_input(void)
{
	printf(CLR_BLUE"[%s]\n"CLR_RST, ms()->cwd);
	while (1)
	{
		ms()->input = readline(PROMPT);
		if (ms()->input && ft_strlen(ms()->input) != 0)
			break ;
		else if (ms()->input)
			free(ms()->input);
		else
			no_leaks(1);
	}
}
