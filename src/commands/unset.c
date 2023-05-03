/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crypto <crypto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:31:44 by crypto            #+#    #+#             */
/*   Updated: 2023/05/03 18:31:53 by crypto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **names)
{
	int	i;
	
	i = -1;
	while (names[++i])
	{
		ft_list_remove_if(&ms()->env, names[i], env_key_compare, env_destroy);
		ft_list_remove_if(&ms()->tmp, names[i], env_key_compare, env_destroy);
	}
	(ms()->exit_status) = 0;
	(ms()->path) = ft_split(get_env("PATH"), ':');
}