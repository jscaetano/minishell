/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:09:10 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/06 17:42:18 by marvin           ###   ########.fr       */
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

	env = env_find(ms()->envtmp, name);
	if (!env)
		return ;
	tmp = env_find(ms()->envlist, name);
	if (tmp)
	{
		ft_free(tmp->value);
		tmp->value = ft_strdup(env->value);
	}
	else
		ft_lstadd_front(&ms()->envlist, ft_lstnew(env_copy(env)));
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
			export_directly(&ms()->envlist, vars[i]);
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
			export_directly(&ms()->envtmp, ft_strdup(token->str));
			return (true);
		}
	}
	return (false);
}

char	**envlist_to_matrix(t_list *envlist)
{
	char 	**matrix;
	t_env	*env;
	char	*tmp1;
	char	*tmp2;
	
	matrix = ft_calloc(1, sizeof(char *));
	if (!matrix)
		return (NULL);
	while (envlist)
	{
		env = (t_env *)envlist->content;
		tmp1 = ft_strjoin(env->key, "=");
		tmp2 = ft_strjoin(tmp1, env->value);
		matrix = matrix_append(matrix, ft_strdup(tmp2));
		free(tmp1);
		free(tmp2);
		envlist = envlist->next;
	}
	return (matrix);
}
