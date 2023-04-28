/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:09:10 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/28 14:00:33 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if (!ft_strcmp(tmp->key, env->key))
// {
// 	if (tmp->value != NULL)
// 		env->value = tmp->value;
// 	tmp->value = NULL;
// 	free (new);
// 	return ;
// }

//export (add a=x expression, if previously stored in tmp to env)
/* void	ft_export(char **tokens)
{
	int		i;
	t_var	*tmp;
	t_var	*env;
	t_var	*new;

	if (is_assignment(1))
	{
		if (!ft_strcmp(get_env(tokens[1]), ""))
			tokens[1] = ms()->tmp->top->key;
	}
	i = 0;
	// For each variable in the export command
	while (tokens[++i])
	{
		tmp = ms()->tmp->top;
		// For each variable in the temporary variables list
		while (tmp)
		{
			// If I find the name of the variable Im trying to export
			if (!ft_strcmp(tmp->key, tokens[i]))
			{
				env = get_var_node(tokens[i]);
				if (env)
				{
					if (tmp->value)
					{
						ft_free(env->value);
						env->value = ft_strdup(tmp->value);
					}
				}
				// Otherwise append it
				else
				{
					new = var_new(ft_strdup(tmp->key), ft_strdup(tmp->value));
					new->next = ms()->env->top;
					(ms()->env->top) = new;
					(ms()->env->size++);					
				}
			}
			tmp = tmp->next;
		}
	}
	(ms()->path) = ft_split(get_env("PATH"), ':');
} */

void	export_directly_to_env(char *assignment)
{
	t_var	*var;
	char	*name;
	char	*value;
	int		i;
	
	i = ft_strlen_sep(assignment, "=");
	name = ft_strndup(assignment, i);
	value = ft_strdup(assignment + i + 1);
	var = find_env(ms()->env, name);
	// If the variable exists in env
	if (var)
	{
		ft_free(name);
		ft_free(var->value);
		var->value = value;
	}
	// Else create a new one and append it
	else
	{
		var = var_new(name, value);
		var->next = ms()->env->top;
		(ms()->env->top) = var;
	}
}

void	export_from_temp_list(char *variable)
{
	t_var	*var;
	t_var	*new;
	
	var = find_env(ms()->tmp, variable);
	if (!var)
		return ;
	new = var_copy(var);
	new->next = ms()->env->top;
	(ms()->env->top) = new;
}

void	ft_export (char **vars)
{
	int	i;

	i = 0;
	while (vars[++i])
	{
		if (is_assignment(1))
			export_directly_to_env(vars[i]);
		else	
			export_from_temp_list(vars[i]);	
	}
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
				(ms()->tmp->size--);
				if (prev)
					prev->next = tmpenv->next;
				else
					(ms()->tmp->top) = tmpenv->next;
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
					(ms()->env->top) = tmpenv->next;
				(ms()->env->size--);
			}
			prev = tmpenv;
			tmpenv = tmpenv->next;
		}
		i++;
	}
	(ms()->path) = ft_split(get_env("PATH"), ':');
}

//if there is a a=x expression, store it in tmp
bool	is_assignment(int token_to_check)
{
	int		j;
	t_token	*token;

	if (token_to_check == 0)
		token = (t_token *)ms()->lexemes->content;
	else
		token = (t_token *)ms()->lexemes->next->content;
	j = 0;
	while (token->str[j])
	{
		if (token->str[j] == '=')
		{
			ft_stackpush(ms()->tmp, ft_strdup(token->str));
			return (true);
		}
		j++;
	}
	return (false);
}
