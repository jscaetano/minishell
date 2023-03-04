/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncarvalh <ncarvalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:37:44 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/04 18:16:37 by ncarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strncpy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && size--)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*dest;
	int		srcsize;
	char	*str;

	str = (char *)s1;
	srcsize = 0;
	while (s1[srcsize] != '\0')
		srcsize++;
	dest = malloc((srcsize + 1));
	ft_strcpy(dest, str);
	return (dest);
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
	ft_strncpy(dest, str, size);
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	int		i;
	int		j;

	i = 0;
	j = 0;
	r = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i] != '\0')
	{
		r[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		r[i++] = s2[j++];
	}
	r[i] = '\0';
	return (r);
}
