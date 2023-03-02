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

#include "./inc/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int i;

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

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_free(void *p)
{
	if (p)
		free(p);
}

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

void no_leaks(int end)
{
	int	i;

	i = 0;
	ft_free(g_ms.input);
	if (!g_ms.tokensfreed)
	{
		while (g_ms.tokens[i])
			ft_free(g_ms.tokens[i++]);
		ft_free(g_ms.tokens);
		g_ms.tokensfreed = 1;
	}
	printf("\n");
	if (end)
	{
		ft_free(g_ms.cwd);
		exit(EXIT_SUCCESS);
	}
}
