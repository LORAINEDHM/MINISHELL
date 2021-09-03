/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:11:55 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/05 17:40:47 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size1;
	size_t	size2;
	char	*ptr;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2) + 1;
	ptr = malloc(size1 + size2);
	if (!ptr)
		return (NULL);
	ft_memcpy(ptr, s1, size1);
	ft_memcpy(ptr + size1, s2, size2);
	return (ptr);
}
