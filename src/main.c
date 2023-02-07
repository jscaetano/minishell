/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:01:13 by joacaeta          #+#    #+#             */
/*   Updated: 2023/02/07 18:26:52 by joacaeta         ###   ########.fr       */
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

char	*get_env(char *str)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 0;
	while (g_ms.env[i])
	{
		if (!ft_strncmp(g_ms.env[i], str, len))
		{
			if (g_ms.env[i][len] == '=')
				return (g_ms.env[i] + len + 1);
		}
		i++;
	}
	return (NULL);
}

static void	fill_args(char **envv)
{
	if (g_ms.cwd)
		free(g_ms.cwd);
	g_ms.env = envv;
	g_ms.path = ft_split(get_env("PATH"), ':');
	g_ms.cwd = getcwd(NULL, 4096);
	return ;
}

void	env()
{
	int	i;

	i = 0;
	while (g_ms.env[i])
		printf("%s\n", g_ms.env[i++]);
}

void	handle_input()
{
	if (!ft_strcmp(g_ms.input, "exit"))
		no_leaks();
	else if (!ft_strcmp(g_ms.input, "pwd"))
		printf("%s\n", g_ms.cwd);
	else if (!ft_strcmp(g_ms.input, "env"))
		env();

	// printf("%s\n", g_ms.cwd);
	// else if (!ft_strcmp(g_ms.input, "pwd"))

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
		add_history(g_ms.input);
		handle_input();

		// printf("%s\n", g_ms.input);
		free(g_ms.input);
	}
	return (0);
}
