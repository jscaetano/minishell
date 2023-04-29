/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:56:43 by ncarvalh          #+#    #+#             */
/*   Updated: 2023/04/29 11:19:39 by ncarvalh         ###   ########.fr       */
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
