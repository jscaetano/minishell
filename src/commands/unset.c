/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:31:44 by crypto            #+#    #+#             */
/*   Updated: 2023/05/06 19:34:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **names)
{
	int	i;

	i = -1;
	(ms()->exit_status) = 0;
	while (names[++i])
	{
		ft_list_remove_if(&ms()->envlist, names[i], env_key_compare, env_destroy);
		ft_list_remove_if(&ms()->envtmp, names[i], env_key_compare, env_destroy);
	}
}
