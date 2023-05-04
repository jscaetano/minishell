/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:09:10 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/04 09:56:39 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Pushed a new variable to an envlist either tmp or env
void	export_directly(t_list **envlist, char *assignment)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*env;

	i = ft_strlen_sep(assignment, "=");
	name = ft_strndup(assignment, i);
	value = ft_strdup(assignment + i + 1);
	env = env_find(*envlist, name);
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

	env = env_find(ms()->tmp, name);
	if (!env)
		return ;
	tmp = env_find(ms()->env, name);
	if (tmp)
	{
		ft_free(tmp->value);
		tmp->value = ft_strdup(env->value);
	}
	else
		ft_lstadd_front(&ms()->env, ft_lstnew(env_copy(env)));
}

void	ft_export(char **vars)
{
	int		i;
	t_list	*lexeme;

	i = -1;
	lexeme = ms()->lexemes->next;
	while (vars[++i])
	{
		if (is_assignment(lexeme->content))
			export_directly(&ms()->env, vars[i]);
		else
			export_from_temp_list(vars[i]);
		lexeme = lexeme->next;
	}
	(ms()->exit_status) = 0;
	(ms()->path) = ft_split(get_env("PATH"), ':');
}

//if there is a a=x expression, store it in tmp (old find_equals)
bool	is_assignment(t_token *token)
{
	int	i;

	i = -1;
	while (token->str[++i])
	{
		if (token->str[i] == '=')
		{
			export_directly(&ms()->tmp, ft_strdup(token->str));
			return (true);
		}
	}
	return (false);
}
