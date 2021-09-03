/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:10:01 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/07 21:37:00 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	size_t	i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	size;

	size = get_size(n);
	ptr = ft_calloc(size + 1, 1);
	if (!ptr)
		return (NULL);
	if (n < 0)
		*ptr = '-';
	while ((size > 0 && *ptr != '-') || size > 1)
	{
		if (n < 0)
			*(ptr + --size) = -(n % -10) + '0';
		else
			*(ptr + --size) = n % 10 + '0';
		n /= 10;
	}
	return (ptr);
}
