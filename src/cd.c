/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:24:50 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/02 19:41:07 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_cwd_len(int slash)
{
	int	len;
	int	i;

	len = 0;
	i = 0;


	slash++;
	while (slash)
	{
		if (g_ms.cwd[i] == '/')
			slash--;
		len++;
		i++;
	}
	return (len - 1);
}

int	cd_backwards()
{
	int		ddot;
	int		slash;
	int		i;
	int		cwdlen;
	char	*tmpcwd;

	i = 0;
	ddot = 0;
	slash = 0;
	while (g_ms.tokens[1][i])
	{
		if (g_ms.tokens[1][i++] == '.' && g_ms.tokens[1][i++] == '.')
			ddot++;
		else if (g_ms.tokens[1][i] == '/')
			i++;
		else
			break ;
	}
	i = 0;
	while (g_ms.cwd[i])
	{
		if (g_ms.cwd[i] == '/')
			slash++;
		i++;
	}
	i = 0;
	slash = slash - ddot;
	cwdlen = new_cwd_len(slash);
	tmpcwd = malloc(sizeof(char) * cwdlen + 1);
	if (slash > 0)
	{
		while (cwdlen)
		{
			tmpcwd[i] = g_ms.cwd[i];
			cwdlen--;
			i++;
		}
		tmpcwd[i] = '\0';
		g_ms.cwd = tmpcwd;
		return (1);
	}
	return (0);
}

void	cd()
{
	struct stat	stats;
	int			i;


	i = 0;
	stat(g_ms.tokens[1], &stats);

	//same dir
	if (!ft_strcmp(g_ms.tokens[1], "."))
		return ;

	//backwards dir
	if (cd_backwards())
		return ;

	//absolute dir
	if (S_ISDIR(stats.st_mode))
	{
		g_ms.cwd = g_ms.tokens[1];
	}
	else
		printf("cd: no such file or directory: %s\n", g_ms.tokens[1]);
}
