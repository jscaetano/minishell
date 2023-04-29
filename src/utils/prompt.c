/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:56:43 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/04/29 11:17:33 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_prompt()
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strrchr(ms()->cwd, '/');
	tmp1 = ft_strdup(tmp1);
	tmp2 = ft_strjoin(CLR_BLUE"[", tmp1);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, "]"CLR_RST);
	free(tmp2);
	tmp2 = ft_strjoin(tmp1, " ");
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, "minishell > ");
	free(tmp2);
	return (tmp1);
}

/* 
// Get the name of the folder I am currently in using the ms struct
	char *tmp;
	char *folder;
	
	tmp = ft_strrchr(ms()->cwd, '/');
	
	folder = ft_strdup(tmp);
	// Append the red color with the name of the folder I am currently in
	tmp = ft_strjoin("\033[0;31m", folder);
	// Append the reset color
	folder = ft_strjoin(tmp, "\033[0m");
	free(tmp);

	//Append a space
	tmp = ft_strjoin(folder, " ");
	free(folder);
	folder = tmp;
	
	// Append the "minishell > " string with the so far built string with a separating space and the reset color in the end
	tmp = ft_strjoin(folder, "minishell > ");
	free(folder);
	// Append the reset color in the end of the string
	folder = ft_strjoin(tmp, "\033[0m");
	free(tmp);
	return (folder); */