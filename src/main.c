/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:01:13 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/02 19:36:43 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_args(char **envv)
{
	ft_bzero(ms(), sizeof(t_ms));
	(ms()->envlist) = envlist(envv);
	update_envs();
	(ms()->exit_status) = 0;
	(ms()->cwd) = getcwd(NULL, 4096);
	(ms()->in_fd) = STDIN_FILENO;
	(ms()->out_fd) = STDOUT_FILENO;
	return ;
}

//add
int	main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;
	fill_args(envv);
	signals();
	reader();
	return (0);
}
