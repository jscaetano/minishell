/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:31:44 by crypto            #+#    #+#             */
/*   Updated: 2023/05/06 21:06:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **var)
{
	int	i;

	i = -1;
	(ms()->exit_status) = 0;
	while (var[++i])
	{
		ft_list_remove_if(&ms()->envlist, var[i], env_key_compare, env_destroy);
		ft_list_remove_if(&ms()->envtmp, var[i], env_key_compare, env_destroy);
	}
}
