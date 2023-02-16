/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 17:01:13 by joacaeta          #+#    #+#             */
/*   Updated: 2023/02/16 15:25:54 by ncarvalh         ###   ########.fr       */
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
		else
			no_leaks(1);
	}
}

char	*get_env(char *str)
{
	int		i;
	int		len;

	i = 0;
	if (str[0] == '$')
		str++;
	len = ft_strlen(str);
	while (g_ms.env[i])
	{
		if (!ft_strncmp(g_ms.env[i], str, len))
		{
			if (g_ms.env[i][len] == '=')
				return (ft_strdup(g_ms.env[i] + len + 1));
		}
		i++;
	}
	return (str);
}

static void	fill_args(char **envv)
{
	if (g_ms.cwd)
		free(g_ms.cwd);
	g_ms.env = envv;
	g_ms.path = ft_split(get_env("PATH"), ':');
	g_ms.cwd = getcwd(NULL, 4096);
	g_ms.tokensfreed = 1;
	g_ms.lexer = new_lexer(0);
	return ;
}

void	env()
{
	int	i;

	i = 0;
	while (g_ms.env[i])
		printf("%s\n", g_ms.env[i++]);
}

void	echo()
{
	int		i;
	int		size;
	char	*tmp;

	size = 0;
	i = 1;
	while (g_ms.tokens[i])
	{
		if (g_ms.tokens[i][0] == '$')
		{
			size = ft_strlen(get_env(g_ms.tokens[i]));
			tmp = malloc(sizeof(char) * (size + 1));
			tmp = get_env(g_ms.tokens[i]);
			ft_free(g_ms.tokens[i]);
			g_ms.tokens[i] = malloc(sizeof(char) * (size));
			g_ms.tokens[i] = tmp;
		}
		printf("%s ", g_ms.tokens[i++]);
	}
}

void	handle_input()
{
	int	i;

	i = 0;
	lexer(&g_ms);
	print_lexer(&g_ms.lexer);
	g_ms.tokens = ft_split(g_ms.input, ' ');
	g_ms.tokensfreed = 0;
	if (!ft_strcmp(g_ms.tokens[0], "exit"))
		no_leaks(1);
	else if (!ft_strcmp(g_ms.tokens[0], "pwd"))
		printf("%s\n", g_ms.cwd);
	else if (!ft_strcmp(g_ms.tokens[0], "env"))
		env();
	else if (!ft_strcmp(g_ms.tokens[0], "echo"))
		echo();
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
		//no_leaks(0);
	}
	return (0);
}
