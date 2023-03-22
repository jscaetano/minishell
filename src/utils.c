/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joacaeta <joacaeta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:41:55 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/02 16:06:36 by joacaeta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 != '\0') && (*s2 != '\0') && (n > 0))
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int		ft_strlen_delim(const char *s, char delim, int symbols)
{
	int	i;

	i = 0;
	if (symbols)
	{
		while (s[i] && s[i] != delim && s[i] != '<' && s[i] != '>' \
			&& s[i] != '\'' && s[i] != '"' && s[i] != '|')
			i++;
	}
	else
	{
		while (s[i] && s[i] != delim)
			i++;
	}
	return (i);
}

int		ft_strlen_delim_alnum(const char *s)
{
	int	i;

	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}
