/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:12:27 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/05 17:41:57 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	size;

	size = ft_strlen(needle);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && size <= len--)
		if (!ft_strncmp(haystack++, needle, size))
			return ((char *)haystack - 1);
	return (NULL);
}
