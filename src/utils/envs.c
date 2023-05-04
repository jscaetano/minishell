/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:13:12 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/04 10:04:11 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	return (new);
}

t_env	*env_copy(t_env	*env)
{
	t_env	*copy;

	copy = env_new(ft_strdup(env->key), ft_strdup(env->value));
	if (!copy)
		return (NULL);
	return (copy);
}

t_env	*env_find(t_list *envs, char *key)
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

bool	env_key_compare(t_env *env, char *key)
{
	return (ft_strcmp(env->key, key) == 0);
}

void	env_destroy(t_env *env)
{
	ft_free(env->key);
	ft_free(env->value);
	ft_free(env);
}
