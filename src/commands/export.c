/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:09:10 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/09 18:01:46 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_assignment(t_token *token)
{
	int	i;

	i = -1;
	if (token->str[0])
	{
		if (token->str[0] == '=' || token->str[ft_strlen(token->str) - 1] == '=')
		{
			error(ANSI_RED, ERROR_BAD_ASSIGNMENT, NULL, 1);
			return (false);
		}
	}
	while (token->str[++i])
	{
		if (token->str[i] == '=')
		{
			export_directly(&ms()->envtmp, token->str);
			return (true);
		}
	}
	return (false);
}

t_env	*_env_find(t_list *envs, char *key)
{
	t_list	*curr;
	t_env	*env;

	if (!envs)
		return (NULL);
	curr = envs;
	while (curr)
	{
		env = (t_env *)curr->content;
		if (!ft_strcmp(env->key, key))
			return (env);
		curr = curr->next;
	}
	return (NULL);
}

void	_export_from_temp_list(char *name)
{
	t_env	*env;
	t_env	*temp;

	temp = _env_find(ms()->envtmp, name);
	if (!temp)
		return ;
	env = _env_find(ms()->envlist, name);
	if (env)
	{
		ft_free(env->value);
		env->value = ft_strdup(temp->value);
	}
	else
		ft_lstadd_front(&ms()->envlist, ft_lstnew(env_copy(temp)));
}

void	export_directly(t_list **envlist, char *assignment)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*env;

	i = ft_strlen_sep(assignment, "=");
	name = ft_substr(assignment, 0, i);
	value = ft_strdup(assignment + i + 1);
	env = _env_find(*envlist, name);
	if (env)
	{
		free(name);
		free(env->value);
		env->value = value;
	}
	else
		ft_lstadd_front(envlist, ft_lstnew(env_new(name, value)));
}

void	ft_export(char **vars)
{
	int		i;
	t_env	*env;
	t_list	*curr;

	i = -1;
	curr = ms()->lexemes->next;
	while (vars[++i])
	{
		if (is_assignment(curr->content))
			export_directly(&ms()->envlist, vars[i]);
		else
			_export_from_temp_list(vars[i]);
		curr = curr->next;
	}
	if (vars[0] != NULL)
		return ;
	curr = ms()->envlist;
	while (curr)
	{
		env = curr->content;
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		curr = curr->next;
	}
}
