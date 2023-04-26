/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:13:12 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/26 09:18:08 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pushes to tmp, if new name, else changes content to the new one
void	ft_stackpush(t_env *env, char *equal)
{
	int		i;
	char	*name;
	t_var	*tmp;
	t_var	*new;

	i = 0;
	tmp = env->top;
	while (equal[i] != '=')
		i++;
	name = ft_strndup(equal, i);
	if (tmp)
	{
		while (tmp)
		{
			if (!ft_strcmp(tmp->key, name))
			{
				i++;
				tmp->value = ft_strdup(equal + i);
				return ;
			}
			tmp = tmp->next;
		}
	}
	new = malloc(sizeof(t_var));
	new->key = name;
	i++;
	new->value = ft_strdup(equal + i);
	new->next = env->top;
	env->top = new;
	env->size++;
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
