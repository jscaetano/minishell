/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:24:33 by marvin            #+#    #+#             */
/*   Updated: 2023/05/06 18:24:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(void)
{
	t_list	*curr;
	t_token	*lexeme;

	curr = ms()->lexemes;
	while (curr)
	{
		lexeme = ((t_token *)curr->content);
		if (lexeme->type == LEX_DOUBLE_QUOTES || lexeme->type == LEX_TERM)
			expand_variable(lexeme);
		curr = curr->next;
	}
}

char	*find_key(char *str)
{
	char	*tmp;
	char	*var;
	int		len;

	len = 0;
	tmp = ft_strnstr(str, "$", ft_strlen(str));
	if (tmp[1] == '?')
		return (ft_strdup("$?"));
	while (ft_isalnum(tmp[len + 1]) || tmp[len + 1] == '_')
		len++;
	var = ft_strndup(tmp, len + 1);
	return (var);
}

void	expand_variable(t_token *token)
{
	char	*value;
	char 	*key;
	char	*tmp;

	while (ft_strnstr(token->str, "$", ft_strlen(token->str)))
	{
		key = find_key(token->str);
		if (!ft_strcmp(key, "$?"))
			value = ft_itoa(ms()->exit_status);
		else
			value = get_env(key);
		tmp = token->str;
		token->str = ft_strreplace(token->str, key, value);
		ft_free(tmp);
		ft_free(value);
		ft_free(key);
	}
}