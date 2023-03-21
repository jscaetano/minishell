/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/21 22:31:10 by joacaeta         ###   ########.fr       */
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

int	double_quotes(t_token *token, int i)
{
	char	*cpy;
	int		j;
	char	*str;
	// char	*env;
	// int		r;

	str = token->str;
	// r = 0;
	cpy = ft_strndup(str, i);

	printf("copy: %s\n", cpy);
	sleep(3);

	j = i + 1;
	while (str[j] && str[j] != '\"')
	{
		if (str[j] == '$')
		{
			// env = get_env(ft_substr(&str[j + 1], 0, ft_strlen_delim(&str[j + 1], 0, 1)));
			// r += (ft_strlen(env) - ft_strlen_delim(&str[j + 1], 0, 1));
			cpy = ft_strjoin(cpy, get_env(ft_substr(&str[j + 1], 0, ft_strlen_delim(&str[j + 1], 0, 1))));
			j += ft_strlen_delim(&str[j + 1], 0, 1);
		}
		j++;
	}

	printf("copy: %s\n", cpy);
	sleep(3);

	cpy = ft_strjoin(cpy, ft_strdup(&str[j + 1]));

	printf("copy: %s\n", cpy);
	sleep(3);
	token->str = cpy;
	return (0);
}

int	single_quotes(t_token *token, int i)
{
	char	*str;

	str = token->str;
	(void)i;
	return i;
}

void	deal_quotes()
{
	t_list	*tmplist;
	t_token *tmptoken;
	int		i;

	tmplist = ms()->lexemes;
	while (tmplist)
	{
		i = 0;
		tmptoken = ((t_token *)tmplist->content);
		if (tmptoken->type != LEX_TERM)
			continue;
		while(tmptoken->str[i])
		{
			if (tmptoken->str[i] == '"')
				double_quotes(tmptoken, i);
			else if (tmptoken->str[i] == '\'')
				single_quotes(tmptoken, i);
			i++;
		}
		tmplist = tmplist->next;
	}
}

void	handle_input(void)
{
	char	**tokens;

	lexer(ms());
	deal_quotes();
	token_args();
	// print_lexer_args();
	ms()->ast = parser();
	#ifdef DEBUG
		//ast_print(ms()->ast, 0, &token_print);
		print_lexer_args();
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
