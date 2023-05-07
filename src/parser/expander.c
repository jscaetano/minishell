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

char	*_find_key(char *str)
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
	var = ft_substr(tmp, 0, len + 1);
	return (var);
}

void	_expand_variable(t_token *token)
{
	char	*value;
	char	*key;
	char	*tmp;

	while (ft_strnstr(token->str, "$", ft_strlen(token->str)))
	{
		key = _find_key(token->str);
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

void	expander(void)
{
	t_list	*curr;
	t_token	*token;

	curr = ms()->lexemes;
	while (curr)
	{
		token = ((t_token *)curr->content);
		if (token->type == LEX_DOUBLE_QUOTES || token->type == LEX_TERM)
			_expand_variable(token);
		curr = curr->next;
	}
}
