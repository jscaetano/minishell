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

int	is_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\f' && str[i] != '\n'
		&& str[i] != '\r' && str[i] != '\t'
		&& str[i] != '\v' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int		ft_strlen_sep(const char *s, char *seps)
{
	int	i;

	i = 0;
	while (s[i] && !ft_strchr(seps, s[i]))
		i++;
	return (i);
}

int		ft_strlen_sep_alnum(const char *s)
{
	int	i;

	i = 0;
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}

char	*ft_strndup(const char *s1, int size)
{
	char	*dest;
	int		srcsize;
	char	*str;
	int		tmpsize;

	tmpsize = size;
	str = (char *)s1;
	srcsize = 0;
	while (s1[srcsize] != '\0' && tmpsize--)
		srcsize++;
	dest = malloc((srcsize + 1));
	ft_strlcpy(dest, str, size + 1);
	return (dest);
}

bool	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (false);
	return (true);
}

