/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:10:52 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/05 17:39:27 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*ptr1;

	ptr1 = s;
	while (n-- > 0)
		if (*ptr1++ == (char)c)
			return ((char *)ptr1 - 1);
	return (NULL);
}
