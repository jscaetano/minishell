/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:09:10 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/28 18:01:28 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pushes to tmp, if new name, else changes content to the new one
void	export_directly(t_list **envlist, char *assignment)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*env;

	i = ft_strlen_sep(assignment, "=");
	name = ft_strndup(assignment, i);
	value = ft_strdup(assignment + i + 1);
	env = find_env(*envlist, name);
	if (env)
	{
		free(name);
		free(env->value);
		env->value = value;
	}
	else
		ft_lstadd_front(envlist, ft_lstnew(env_new(name, value)));
}
// Exports the variable from the temporary list
void	export_from_temp_list(char *name)
{
	t_env	*tmp;
	t_env	*env;
	
	env = find_env(ms()->new_tmp, name);
	if (!env)
		return ;
	tmp = find_env(ms()->new_env, name);
	if (tmp)
	{
		ft_free(tmp->value);
		tmp->value = ft_strdup(env->value);
	}
	else
		ft_lstadd_front(&ms()->new_env, ft_lstnew(env_copy(env)));
}

void	ft_export(char **vars)
{
	int	i;

	i = -1;
	while (vars[++i])
	{
		if (is_assignment(1))
			export_directly(&ms()->new_env, vars[i]);
		else	
			export_from_temp_list(vars[i]);	
	}
}

void	ft_unset(char **names)
{
	int	i;
	
	i = -1;
	while (names[++i])
	{
		ft_list_remove_if(&ms()->new_env, names[i], env_compare, env_destroy);
		ft_list_remove_if(&ms()->new_tmp, names[i], env_compare, env_destroy);
	}
	// Isn't this necessary in export as well?
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
	j = -1;
	while (token->str[++j])
	{
		if (token->str[j] == '=')
		{
			export_directly(&ms()->new_tmp, ft_strdup(token->str));
			return (true);
		}
	}
	return (false);
}
