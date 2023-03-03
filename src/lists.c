/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:13:12 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/03 19:13:40 by joacaeta         ###   ########.fr       */
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
			if (!ft_strcmp(tmp->name, name))
			{
				i++;
				tmp->content = ft_strdup(equal + i);
				return ;
			}
			tmp = tmp->next;
		}
	}
	new = malloc(sizeof(t_var));
	new->name = name;
	i++;
	new->content = ft_strdup(equal + i);
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
