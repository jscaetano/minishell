/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:01:13 by joacaeta          #+#    #+#             */
/*   Updated: 2023/01/30 18:52:47 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

t_ms g_ms;

static void	sigint_action(int signal)
{
	rl_replace_line("", signal);
	printf("\n");
	printf(CLR_BLUE"\n[%s]\n"CLR_RST, g_ms.cwd);
	rl_on_new_line();
	rl_redisplay();
}

static void	read_input()
{
	printf(CLR_BLUE"\n[%s]\n"CLR_RST, g_ms.cwd);
	while (1)
	{
		g_ms.input = readline(PROMPT);
		if (g_ms.input && ft_strlen(g_ms.input) != 0)
			break ;
		else if (g_ms.input)
			free(g_ms.input);
		else if (!g_ms.input)
			no_leaks();
	}
}

static void	fill_args(char **envv)
{
	int	i;

	i = 0;
	if (g_ms.cwd)
		free(g_ms.cwd);
	while(envv[i])
	{
		if (envv[i][0] == 'P' && envv[i][1] == 'A' && envv[i][2] == 'T'
			&& envv[i][3] == 'H' && envv[i][4] == '=')
		{
			g_ms.path = ft_split(envv[i] + 5,':');
			break ;
		}
		i++;
	}
	g_ms.cwd = getcwd(NULL, 4096);
	return ;
}

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
		if (!ft_strcmp(g_ms.input, "exit"))
			no_leaks();
		printf("%s\n", g_ms.input);
		free(g_ms.input);
	}
	return (0);
}
