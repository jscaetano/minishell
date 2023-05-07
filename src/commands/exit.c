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

static bool	is_longlong(char *num)
{
	return (ft_isnum(num) \
		&& ft_strcmp(num, "-9223372036854775808") >= 0 \
		&& ft_strcmp(num, "9223372036854775807") <= 0);
}

void	ft_exit(char **args)
{
	char	*status;

	(ms()->exit_status) = 0;
	if (matrix_size(args) > 1)
	{
		error(ANSI_RED, ERROR_EXIT_MANY_ARGS, NULL, 1);
		return ;
	}
	status = args[0];
	if (status)
	{
		if (!is_longlong(status))
			error(ANSI_RED, ERROR_EXIT_NO_NUM, NULL, 2);
		else
			(ms()->exit_status) = (unsigned char) ft_atoull(status);
	}	
	sanitize(true);
}
