/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:00:16 by marvin            #+#    #+#             */
/*   Updated: 2023/05/02 19:00:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == '\f' || c == '\n'
		|| c == '\r' || c == '\t'
		|| c == '\v' || c == ' ');
}

unsigned long long	ft_atoull(const char *nptr)
{
	int					i;
	unsigned long long	res;
	int					signal;

	i = 0;
	res = 0;
	signal = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signal = -1;
		i++;
	}
	while (ft_isdigit(nptr[i]))
		res = res * 10 + nptr[i++] - '0';
	return (signal * res);
}
/*
int main(int argc, char **argv)
{
	(void) argc;

	printf("\n\t>>> USING ft_atoi() <<<\n\n");
	printf("Sending str = \'%s\'\n", argv[1]);
	printf("Resulting in: %d\n", ft_atoi(argv[1]));

	printf("\n\t>>> USING atoi() <<<\n\n");
	printf("Sending str = \'%s\'\n", argv[1]);
	printf("Resulting in: %d\n", atoi(argv[1]));
}
 */
