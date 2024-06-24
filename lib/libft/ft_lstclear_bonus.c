/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkaiser <dkaiser@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 16:26:23 by dkaiser           #+#    #+#             */
/*   Updated: 2024/03/11 12:48:24 by dkaiser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (*lst)
	{
		current = *lst;
		while (current->next)
		{
			next = current->next;
			ft_lstdelone(current, del);
			current = next;
		}
		ft_lstdelone(current, del);
	}
	*lst = NULL;
}
