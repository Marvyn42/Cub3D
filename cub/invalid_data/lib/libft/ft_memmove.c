/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:07:21 by mamaquig          #+#    #+#             */
/*   Updated: 2019/11/08 19:34:49 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*ptrdst;
	unsigned char	*ptrsrc;

	ptrdst = (unsigned char*)dst;
	ptrsrc = (unsigned char*)src;
	i = 0;
	if (dst == NULL && src == NULL)
		return (0);
	if (ptrsrc < ptrdst)
		while (i < len)
		{
			i++;
			ptrdst[len - i] = ptrsrc[len - i];
		}
	else
		while (len > 0)
		{
			ptrdst[i] = ptrsrc[i];
			i++;
			len--;
		}
	return (dst);
}
