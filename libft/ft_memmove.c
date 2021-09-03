/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:11:05 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/02 13:03:42 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	if (!(!dst && !src))
	{
		ptr1 = dst;
		ptr2 = src;
		if (ptr2 < ptr1 && ptr1 < ptr2 + n)
			while (n-- > 0)
				*(ptr1 + n) = *(ptr2 + n);
		else
			ft_memcpy(dst, src, n);
	}
	return (dst);
}
