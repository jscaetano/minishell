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

// static void	sigint_action(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		printf("\n");
// 		printf(CLR_BLUE"[%s]\n"CLR_RST, ms()->cwd);
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// }

static void	fill_args(char **envv)
{
	char	**path;
	char	*cwd;

	if (ms()->cwd)
		free(ms()->cwd);
	ft_bzero(ms(), sizeof(t_ms));
	ms()->envv = envv;
	ms()->env = envlist(envv);
	path = ft_split(get_env("PATH"), ':');
	ms()->path = path;
	ms()->laststatus = 0;
	cwd = getcwd(NULL, 4096);
	ms()->cwd = cwd;
	ms()->lexemes = NULL;
	return ;
}

//add
int	main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;
	fill_args(envv);
	signals();
	read_input();
	return (0);
}
