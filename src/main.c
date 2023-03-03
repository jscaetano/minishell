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

#include "./inc/minishell.h"

static void	sigint_action(int signal)
{
	rl_replace_line("", signal);
	printf("\n");
	printf(CLR_BLUE"[%s]\n"CLR_RST, ms()->cwd);
	rl_on_new_line();
	rl_redisplay();
}

static void	fill_args(char **envv)
{
	if (ms()->cwd)
		free(ms()->cwd);
	ms()->envv = envv;
	ms()->env = envlist(envv);
	ms()->tmp = ft_stacknew();
	ms()->path = ft_split(get_env("PATH"), ':');
	ms()->cwd = getcwd(NULL, 4096);
	ms()->tokensfreed = 1;
	return ;
}

//add
int	main(int argc, char **argv, char **envv)
{
	(void)argc;
	(void)argv;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_action);
	fill_args(envv);
	while (1)
	{
		read_input();
		add_history(ms()->input);
		handle_input();

		// printf("%s\n", ms()->input);
		//no_leaks(0);
	}
	return (0);
}
