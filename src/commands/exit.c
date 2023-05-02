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

void	exit_error(char *arg)
{
	if (arg)
		printf("exit: %s: numeric argument required", arg);
	else
		printf("exit: too many arguments");
	sanitize(true);
}

void	ft_exit(char **args)
{
	char	*arg;
	int		i;

	i = 0;
	arg = args[0];
	ms()->exit_status = 0;
	if (matrix_size(args) == 0)
		sanitize(true);
	if (matrix_size(args) > 1)
		exit_error(NULL);
	if (arg)
	{
		// if (ft_atoull(arg) > LLONG_MAX)
		// 	exit_error(arg);
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
				exit_error(arg);
			i++;
		}
	}
	(ms()->exit_status) = (unsigned char)ft_atoi(arg);
	sanitize(true);
}