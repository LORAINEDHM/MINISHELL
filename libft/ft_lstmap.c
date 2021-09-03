/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:10:36 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/07 22:55:03 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*tmp;
	void	*new_content;

	new_content = (*f)(lst->content);
	if (!new_content)
		return (NULL);
	ptr = ft_lstnew(new_content);
	if (!ptr)
		return (NULL);
	tmp = ptr;
	while (lst->next)
	{
		lst = lst->next;
		new_content = (*f)(lst->content);
		tmp->next = ft_lstnew(new_content);
		if (!tmp->next || !new_content)
		{
			ft_lstclear(&ptr, del);
			del(new_content);
			return (NULL);
		}
		tmp = tmp->next;
	}
	return (ptr);
}
