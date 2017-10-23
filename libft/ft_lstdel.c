/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 17:58:55 by gmichaud          #+#    #+#             */
/*   Updated: 2016/12/01 17:19:16 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp1;
	t_list *tmp2;

	if (alst)
	{
		tmp1 = *alst;
		tmp2 = tmp1;
		while (tmp1)
		{
			tmp1 = tmp1->next;
			del(tmp2->content, tmp2->content_size);
			free(tmp2);
			tmp2 = tmp1;
		}
		*alst = NULL;
	}
}
