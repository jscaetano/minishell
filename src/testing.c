/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:10:59 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/03 19:40:00 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// for testing purposes, print tmp list
void	printtmp(void)
{
	t_var	*tmp;

	tmp = ms()->tmp->top;
	if (!tmp)
		return ;
	while (tmp->next)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
	printf("%s=%s\n", tmp->name, tmp->content);
}
