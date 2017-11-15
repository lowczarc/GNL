/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lowczarc <lowczarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 08:17:07 by lowczarc          #+#    #+#             */
/*   Updated: 2017/11/13 12:06:02 by lowczarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;

	while (*alst != NULL)
	{
		next = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		(*alst) = next;
	}
	*alst = NULL;
}
