/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:45:25 by joacaeta          #+#    #+#             */
/*   Updated: 2023/05/09 18:48:07 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_heredoc(void)
{
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_child(void)
{
	signal(SIGINT, handler_child);
	signal(SIGQUIT, handler_child);
}

void	signals(void)
{
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_2(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
