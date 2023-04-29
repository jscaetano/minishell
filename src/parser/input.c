/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/29 11:24:20 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander()
{
	t_list	*tmplist;
	t_token *tmptoken;

	tmplist = ms()->lexemes;
	while (tmplist)
	{
		tmptoken = ((t_token *)tmplist->content);
		if (tmptoken->type == LEX_DOUBLE_QUOTES || tmptoken->type == LEX_TERM)
			expand_variable(tmptoken);
		tmplist = tmplist->next;
	}
}

void	expand_variable(t_token *token)
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

void	handle_input(void)
{
	if (is_spaces(ms()->input))
		return ;
	lexer();
	expander();
	parser();
	#ifdef DEBUG
		printf("\n\t -------- LEXER --------\n\n");
		lexer_debug();
		printf("\n\t --------- AST ---------\n\n");
		ast_debug(ms()->ast, 0, token_debug); 
	#endif
	return ;
	if (!is_assignment(0))
		execute_command_list(ms()->cmd_list);
	sanitize(false);
}

void	read_input(void)
{
	char 	*prompt;
	// printf(CLR_BLUE"[%s]\n"CLR_RST, ms()->cwd);
	while (1)
	{
		prompt = update_prompt();
		(ms()->input) = readline(prompt);
		if (ms()->input && ft_strlen(ms()->input) != 0)
			break ;
		else if (ms()->input)
			free(ms()->input);
		else
			sanitize(true);
		free(prompt);
	}
}
