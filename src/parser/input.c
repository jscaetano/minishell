/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/25 15:08:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_quotes(t_token *token)
{
	char	*cpy;
	int		i;
	char	*str;
	char	*env;

	str = token->str;
	i = 0;
	cpy = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?')
			{
				i++;
				env = ft_itoa(ms()->laststatus);
			}
			else if (ft_strlen(str) == 1)
			{
				cpy = ft_strjoin(cpy, "$");
				i++;
				continue ;
			}
			else
			{
				env = get_env(ft_substr(&str[i + 1], 0, ft_strlen_sep_alnum(&str[i + 1])));
				i += ft_strlen_sep_alnum(&str[i + 1]);
			}
			cpy = ft_strjoin(cpy, env);
		}
		else
			cpy = ft_strjoin(cpy, ft_strndup(&str[i], 1));
		i++;
	}
	token->str = cpy;
	return ;
}

void	deal_quotes()
{
	t_list	*tmplist;
	t_token *tmptoken;

	tmplist = ms()->lexemes;
	while (tmplist)
	{
		tmptoken = ((t_token *)tmplist->content);
		if (tmptoken->type == LEX_DOUBLE_QUOTES || tmptoken->type == LEX_TERM)
			double_quotes(tmptoken);
		tmplist = tmplist->next;
	}
}

void	handle_input(void)
{
	char	**tokens;

	if (is_spaces((ms()->input)))
		return ;
	lexer(ms());
	deal_quotes();
	ms()->ast = parser();
	ms()->cmd_list = ast_to_list(ms()->ast);
	#ifdef DEBUG
		// t_list *curr;
		// t_ast *aux;
		// curr = ms()->cmd_list;

		// while (curr)
		// {
		// 	aux = (t_ast *)curr->content;
		// 	printf("Command[%d]: %s\n", aux->index, aux->args[0]);
		// 	curr = curr->next;			
		// }
		printf("input: %s\n", ms()->input);
		ast_print(ms()->ast, 0, &token_debug);
		printf("\n\n\n\n");
	#endif
	tokens = ft_split(ms()->input, ' ');
	ms()->tokens = tokens;
	ms()->tokensfreed = 0;
	if (find_equals(0))
	{
		ft_lstclear(&ms()->lexemes, &token_destroy);
		return ;
	}
	printf("Num commands: %d\n", ms()->num_commands);
	if (!ft_strcmp(((t_ast *)ms()->cmd_list->content)->args[0], "exit"))
		no_leaks(1);
	execute_command_list(ms()->cmd_list);
	ft_lstclear(&ms()->lexemes, (void (*)(void *))token_destroy);
	ft_lstclear(&ms()->cmd_list, (void (*)(void *))ast_destroy_node);
	ms()->num_commands = 0;
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
