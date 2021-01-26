/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:38:31 by mamaquig          #+#    #+#             */
/*   Updated: 2019/11/13 11:53:59 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_size(long int n)
{
	int i;

	i = 2;
	if (n < 0)
	{
		i += 1;
		n = -n;
	}
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char		*str;
	size_t		i;
	long int	cp;

	cp = (long int)n;
	i = ft_size(cp);
	if (!(str = malloc(sizeof(char) * i)))
		return (NULL);
	if (cp < 0)
	{
		str[0] = '-';
		cp = -cp;
	}
	str[i - 1] = '\0';
	i--;
	while (((i > 0 && cp > 0) || (cp == 0 && i > 0)) && (str[i - 1] != '-'))
	{
		str[i - 1] = cp % 10 + '0';
		cp = cp / 10;
		i--;
	}
	return (str);
}
