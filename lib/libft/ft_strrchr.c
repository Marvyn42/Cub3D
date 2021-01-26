/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:32:53 by mamaquig          #+#    #+#             */
/*   Updated: 2019/10/11 18:43:05 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *p;

	p = s;
	while (*s != '\0')
	{
		if (*s == c)
			p = s;
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	else if (*s == '\0' && *p == c)
		return ((char *)p);
	return (0);
}
