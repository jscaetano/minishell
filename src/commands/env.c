/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:26:30 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/28 16:44:46 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates and fills the env list with env (including name and content)
t_list	*envlist(char **envp)
{
	t_list	*envlist;
	int		i;

	i = matrix_size(envp);
	envlist = NULL;
	while (--i >= 0)
		export_directly(&envlist, envp[i]);
	return (envlist);
}

// returns the content of the env in env with the name str or just returns ""
char	*get_env(char *str)
{
	t_env	*tmp;
	t_list	*curr;

	if (str[0] == '$')
		str++;
	curr = ms()->new_env;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		if (!ft_strcmp(tmp->key, str))
			return (ft_strdup(tmp->value));
		curr = curr->next;
	}
	return (ft_strdup(""));
}

// env builtin, prints all env
void	ft_env(void)
{
	t_list	*curr;
	t_env	*tmp;

	curr = ms()->new_env;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		printf("%s=%s\n", tmp->key, tmp->value);
		curr = curr->next;
	}
}
