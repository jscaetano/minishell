/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:09:10 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/26 09:18:08 by ncarvalh         ###   ########.fr       */
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
			tokens[1] = ms()->tmp->top->key;
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
			if (!ft_strcmp(tmpenv->key, tokens[i]))
			{
				while (tmp)
				{
					if (!ft_strcmp(tmpenv->key, tmp->key))
					{
						if (tmpenv->value != NULL)
							tmp->value = tmpenv->value;
						tmpenv->value = NULL;
						free (new);
						return ;
					}
					tmp = tmp->next;
				}
				new->key = ft_strdup(tmpenv->key);
				new->value = ft_strdup(tmpenv->value);
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
			if (!ft_strcmp(tmpenv->key, tokens[i]))
			{
				ft_free(tmpenv->key);
				ft_free(tmpenv->value);
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
			if (!ft_strcmp(tmpenv->key, tokens[i]))
			{
				ft_free(tmpenv->key);
				ft_free(tmpenv->value);
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