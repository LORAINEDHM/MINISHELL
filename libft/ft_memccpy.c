/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:10:48 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/02 12:09:50 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		my_c;
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	ptr1 = dst;
	ptr2 = src;
	my_c = c;
	while (n-- > 0)
	{
		*ptr1++ = *ptr2;
		if (*ptr2++ == my_c)
			return (ptr1);
	}
	return (0);
}
