/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaquig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:35:13 by mamaquig          #+#    #+#             */
/*   Updated: 2019/11/08 19:33:58 by mamaquig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *init;
	t_list *tmp;

	init = *lst;
	if (!lst || !del)
		return ;
	while (init)
	{
		tmp = init;
		init = init->next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
