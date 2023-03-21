/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crypto <crypto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:37:44 by joacaeta          #+#    #+#             */
/*   Updated: 2023/03/21 09:22:58 by crypto           ###   ########.fr       */
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
