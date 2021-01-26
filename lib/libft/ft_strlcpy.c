/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:50:53 by mamaquig          #+#    #+#             */
/*   Updated: 2019/11/08 19:35:17 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t srcsize;
	size_t len;

	if (!dst || !src)
		return (0);
	srcsize = ft_strlen(src);
	if (dstsize == 0)
		len = 0;
	else if (srcsize >= dstsize)
		len = dstsize - 1;
	else
		len = srcsize;
	if (dstsize != 0)
	{
		ft_memcpy(dst, src, len);
		dst[len] = '\0';
	}
	return (srcsize);
}
