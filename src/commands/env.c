/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:26:30 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/07 20:50:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *str)
{
	t_env	*tmp;
	t_list	*curr;

	if (str[0] == '$')
		str++;
	curr = ms()->envlist;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		if (!ft_strcmp(tmp->key, str))
			return (ft_strdup(tmp->value));
		curr = curr->next;
	}
	return (ft_strdup(""));
}

void	ft_env(char **tokens)
{
	t_list	*curr;
	t_env	*tmp;

	(ms()->exit_status) = 0;
	if (matrix_size(tokens) > 0)
	{
		error(ANSI_RED, ERROR_EXIT_MANY_ARGS, NULL, 127);
		return ;
	}
	curr = ms()->envlist;
	while (curr)
	{
		tmp = (t_env *)curr->content;
		printf("%s=%s\n", tmp->key, tmp->value);
		curr = curr->next;
	}
}
