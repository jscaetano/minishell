/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:13:12 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/28 14:00:55 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var	*var_new(char *key, char *value)
{
	t_var	*new;
	
	new = ft_calloc(1, sizeof(t_var));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	return (new);
}

t_var	*var_copy(t_var	*var)
{
	t_var	*copy;

	copy = var_new(ft_strdup(var->key), ft_strdup(var->value));
	if (!copy)
		return (NULL);
	return (copy);
}

t_var	*find_env(t_env	*envs, char *key)
{
	t_var	*tmp;

	if (!envs)
		return (NULL);
	tmp = envs->top;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// pushes to tmp, if new name, else changes content to the new one
void	ft_stackpush(t_env *env, char *assignment)
{
	int		i;
	char	*name;
	char	*value;
	t_var	*var;

	i = ft_strlen_sep(assignment, "=");
	name = ft_strndup(assignment, i);
	value = ft_strdup(assignment + i + 1);
	var = find_env(ms()->env, name);
	if (var)
	{
		free(var->value);
		var->value = value;
	}
	else
	{
		var = var_new(name, value);
		var->next = env->top;
		env->top = var;
		env->size++;
	}	
}

// new empty list
t_env	*ft_stacknew(void)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		return (NULL);
	ret->size = 0;
	ret->top = NULL;
	return (ret);
}
