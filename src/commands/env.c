/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:26:30 by joacaeta          #+#    #+#             */
/*   Updated: 2023/04/26 09:18:08 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates and fills the env list with var (including name and content)
t_env	*envlist(char **envv)
{
	t_env	*env;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (envv[i++])
		size++;
	i = size - 1;
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->size = 0;
	env->top = NULL;
	while (i >= 0)
		ft_stackpush(env, envv[i--]);
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
	while (tmp->next)
	{
		if (!ft_strncmp(tmp->key, str, len))
			return (tmp->value);
		tmp = tmp->next;
	}
	if (!ft_strncmp(tmp->key, str, len))
		return (tmp->value);
	return (ft_strdup(""));
}

// env builtin, prints all env
void	ft_env(void)
{
	t_var	*tmp;

	tmp = ms()->env->top;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	printf("%s=%s\n", tmp->key, tmp->value);
}
