/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:09:10 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/26 15:36:44 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//export (add a=x expression, if previously stored in tmp to env)
void	ft_export(char **tokens)
{
	int		i;
	t_var	*tmpenv;
	t_var	*tmp;
	t_var	*new;

	if (find_equals(1))
	{
		if (!ft_strcmp(get_env(tokens[1]), ""))
			tokens[1] = ms()->tmp->top->name;
	}
	i = 1;
	new = malloc(sizeof(t_var));
	tmpenv = ms()->tmp->top;
	tmp = ms()->env->top;
	while (tokens[i])
	{
		tmpenv = ms()->tmp->top;
		while (tmpenv)
		{
			if (!ft_strcmp(tmpenv->name, tokens[i]))
			{
				while (tmp)
				{
					if (!ft_strcmp(tmpenv->name, tmp->name))
					{
						if (tmpenv->content != NULL)
							tmp->content = tmpenv->content;
						tmpenv->content = NULL;
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
	ms()->path = ft_split(get_env("PATH"), ':');
}

//unset (remove a=x expression, if stored in env or in tmp)
void	ft_unset(char **tokens)
{
	int		i;
	t_var	*tmpenv;
	t_var	*prev;

	i = 1;
	while (tokens[i])
	{
		prev = NULL;
		tmpenv = ms()->tmp->top;
		while (tmpenv)
		{
			if (!ft_strcmp(tmpenv->name, tokens[i]))
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
			if (!ft_strcmp(tmpenv->name, tokens[i]))
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
	ms()->path = ft_split(get_env("PATH"), ':');
}

//if there is a a=x expression, store it in tmp
int	find_equals(int token_to_check)
{
	int	j;
	int	r;

	r = 0;
	j = 0;
	while (ms()->tokens[token_to_check][j])
	{
		if (ms()->tokens[token_to_check][j] == '=')
		{
			ft_stackpush(ms()->tmp, ms()->tokens[token_to_check]);
			r = 1;
			break ;
		}
		j++;
	}
	return (r);
}
