/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:12:12 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/05 17:41:42 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	size;

	if (!f)
		return (ft_strdup(s));
	size = ft_strlen(s);
	ptr = malloc(size + 1);
	if (!ptr)
		return (NULL);
	*(ptr + size) = 0;
	while (size-- > 0)
		*(ptr + size) = (*f)(size, *(s + size));
	return (ptr);
}
