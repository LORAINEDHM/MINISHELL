/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:11:51 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/05 17:40:41 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	size;
	char	*ptr;

	size = ft_strlen(s1) + 1;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	return (ft_memcpy(ptr, s1, size));
}
