/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:26:30 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/28 11:26:50 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates and fills the env list with var (including name and content)
t_env	*envlist(char **envp)
{
	t_env	*env;
	int		i;

	i = matrix_size(envp);
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (NULL);
	while (--i >= 0)
		ft_stackpush(env, envp[i]);
	return (env);
}

// returns the content of the var in env with the name str or just returns ""
char	*get_env(char *str)
{
	int		len;
	t_var	*tmp;

	if (str[0] == '$')
		str++;
	len = ft_strlen(str);
	tmp = ms()->env->top;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, str, len))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

// env builtin, prints all env
void	ft_env(void)
{
	t_var	*tmp;

	tmp = ms()->env->top;
	if (!tmp)
		return ;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
