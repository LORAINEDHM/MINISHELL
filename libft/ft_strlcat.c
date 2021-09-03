/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:11:59 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/02 14:17:20 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	offset;

	offset = ft_strlen(dst);
	if (dstsize > offset)
		return (ft_strlcpy(dst + offset, src, dstsize - offset) + offset);
	return (dstsize + ft_strlen(src));
}
