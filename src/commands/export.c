/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crypto <crypto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:09:10 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/03 18:31:27 by crypto           ###   ########.fr       */
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
	int	i;

	i = -1;
	while (vars[++i])
	{
		if (is_assignment(1))
			export_directly(&ms()->env, vars[i]);
		else	
			export_from_temp_list(vars[i]);	
	}
	(ms()->path) = ft_split(get_env("PATH"), ':');
	(ms()->exit_status) = 0;
}

//if there is a a=x expression, store it in tmp (old find_equals)
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
			export_directly(&ms()->tmp, ft_strdup(token->str));
			return (true);
		}
	}
	return (false);
}
