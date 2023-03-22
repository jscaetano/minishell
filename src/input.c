/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/22 21:23:09 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_args(void)
{
	t_list	*node;
	t_token	*token;
	int		i;

	node = ms()->lexemes;
	while (node)
	{
		token = (t_token *)node->content;
		i = 0;
		if (token->type != LEX_DOUBLE_QUOTES && token->type != LEX_SINGLE_QUOTES)
			token->args = ft_split(token->str, ' ');
		else
		{
			token->args = malloc(sizeof(char *) * 2);
			token->args[0] = ft_strdup(token->str);
			token->args[1] = NULL;
		}
		node = node->next;
	}
	return ;
}

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
			env = get_env(ft_substr(&str[i + 1], 0, ft_strlen_sep_alnum(&str[i + 1])));
			cpy = ft_strjoin(cpy, env);
			i += ft_strlen_sep_alnum(&str[i + 1]);
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

	lexer(ms());
	deal_quotes();
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
		ft_echo();
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
	ft_lstclear(&ms()->lexemes, &token_destroy);
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
