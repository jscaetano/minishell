/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:28:42 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/03 19:34:24 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_input()
{
	ms()->tokens = ft_split(ms()->input, ' ');
	ms()->tokensfreed = 0;
	if (find_equals())
		return ;
	if (!ft_strcmp(ms()->tokens[0], "exit"))
		no_leaks(1);
	else if (!ft_strcmp(ms()->tokens[0], "pwd"))
		printf("%s\n", ms()->cwd);
	else if (!ft_strcmp(ms()->tokens[0], "env"))
		ft_env();
	else if (!ft_strcmp(ms()->tokens[0], "echo"))
	{
		if (ms()->tokens[1])
		{
			if (!ft_strcmp(ms()->tokens[1], "-n"))
				ft_echo(1);
			else
				ft_echo(0);
		}
	}
	else if (!ft_strcmp(ms()->tokens[0], "unset"))
		ft_unset();
	else if (!ft_strcmp(ms()->tokens[0], "export"))
		ft_export();
	else if (!ft_strcmp(ms()->tokens[0], "cd"))
		ft_cd();
	else if ((!ft_strcmp(ms()->tokens[0], "ptmp"))) //for testing
		printtmp();
	else
		exec_if_exists(ms()->tokens[0], NULL);
}

void	read_input()
{
	printf(CLR_BLUE"[%s]\n"CLR_RST, ms()->cwd);
	while (1)
	{
		ms()->input = readline(PROMPT);
		if (ms()->input && ft_strlen(ms()->input) != 0)
			break ;
		else if (ms()->input)
			free(ms()->input);
		else
			no_leaks(1);
	}
}
