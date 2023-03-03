/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:09:10 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/03 19:39:38 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//export (add a=x expression, if previously stored in tmp to env)
void	ft_export(void)
{
	int		i;
	t_var	*tmpenv;
	t_var	*tmp;
	t_var	*new;

	i = 1;
	new = malloc(sizeof(t_var));
	tmpenv = ms()->tmp->top;
	tmp = ms()->env->top;
	while (ms()->tokens[i])
	{
		tmpenv = ms()->tmp->top;
		while (tmpenv)
		{
			if (!ft_strcmp(tmpenv->name, ms()->tokens[i]))
			{
				while (tmp)
				{
					if (!ft_strcmp(tmpenv->name, tmp->name))
					{
						tmp->content = tmpenv->content;
						free (new);
						return ;
					}
					tmp = tmp->next;
				}
				new->name = ft_strdup(tmpenv->name);
				new->content = ft_strdup(tmpenv->content);
				new->next = ms()->env->top;
				ms()->env->top = new;
				ms()->env->size++;
			}
			tmpenv = tmpenv->next;
		}
		i++;
	}
}

//unset (remove a=x expression, if stored in env or in tmp)
void	ft_unset(void)
{
	int		i;
	t_var	*tmpenv;
	t_var	*prev;

	i = 1;
	while (ms()->tokens[i])
	{
		prev = NULL;
		tmpenv = ms()->tmp->top;
		while (tmpenv)
		{
			if (!ft_strcmp(tmpenv->name, ms()->tokens[i]))
			{
				ft_free(tmpenv->name);
				ft_free(tmpenv->content);
				ms()->tmp->size--;
				if (prev)
					prev->next = tmpenv->next;
				else
					ms()->tmp->top = tmpenv->next;
			}
			prev = tmpenv;
			tmpenv = tmpenv->next;
		}
		prev = NULL;
		tmpenv = ms()->env->top;
		while (tmpenv)
		{
			if (!ft_strcmp(tmpenv->name, ms()->tokens[i]))
			{
				ft_free(tmpenv->name);
				ft_free(tmpenv->content);
				if (prev)
					prev->next = tmpenv->next;
				else
				{
					ms()->env->top = tmpenv->next;
				}
				ms()->env->size--;
			}
			prev = tmpenv;
			tmpenv = tmpenv->next;
		}
		i++;
	}
}

//if there is a a=x expression, store it in tmp
int	find_equals(void)
{
	int	i;
	int	j;
	int	r;

	r = 0;
	i = 0;
	while (ms()->tokens[i])
	{
		j = 0;
		while (ms()->tokens[i][j])
		{
			if (ms()->tokens[i][j] == '=')
			{
				ft_stackpush(ms()->tmp, ms()->tokens[i]);
				r = 1;
				break ;
			}
			j++;
		}
		i++;
	}
	return (r);
}
