/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 18:50:38 by marvin            #+#    #+#             */
/*   Updated: 2023/05/02 18:50:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **args)
{
	char	*status;

	if (matrix_size(args) > 1)
	{
		message(CLR_RED, ERROR_EXIT_MANY_ARGS, NULL);
		return ;
	}
	ms()->exit_status = 0;
	status = args[0];
	if (status)
	{
		if (!ft_isnum(status) || ft_strcmp(status, "9223372036854775807") > 0)
		{
			message(CLR_RED, ERROR_EXIT_NO_NUM, NULL);
			ms()->exit_status = 2;
		}
		else
			ms()->exit_status = (unsigned char) ft_atoull(status);
	}	
	sanitize(true);
}