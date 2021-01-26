/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:22:06 by mamaquig          #+#    #+#             */
/*   Updated: 2019/11/18 18:41:35 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		s;
	char	*dest;

	s = ft_strlen(s1);
	if (!(dest = malloc(sizeof(char) * s + 1)))
		return (NULL);
	dest = ft_memcpy(dest, s1, s);
	dest[s] = '\0';
	return (dest);
}
