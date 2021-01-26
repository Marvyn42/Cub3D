/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 14:01:25 by mamaquig          #+#    #+#             */
/*   Updated: 2019/11/13 11:50:31 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (ft_strchr((char *)set, s1[start]) && s1[start])
		start++;
	if (end == start)
		return (ft_strdup(""));
	while (ft_strchr((char *)set, s1[end - 1]) && end > start)
		end--;
	return (ft_substr(s1, start, end - start));
}
