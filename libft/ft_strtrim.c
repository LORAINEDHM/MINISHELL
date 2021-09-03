/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:12:41 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/05 17:43:47 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_trimmed_len(char const *s1, char const *set)
{
	size_t	j;

	j = ft_strlen(s1);
	if (!j)
		return (0);
	while (ft_strchr(set, *(s1 + j - 1)))
		j--;
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*ptr;

	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_trimmed_len(s1, set) + 1;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, size);
	return (ptr);
}
