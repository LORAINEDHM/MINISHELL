/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:11:40 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/08/05 15:30:47 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_of_words(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i);
}

static size_t	get_word_len(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	return (i);
}

static char	**ft_clear(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	word_len;
	size_t	j;

	if (!s)
		return (NULL);
	ptr = ft_calloc(sizeof(*ptr), (num_of_words(s, c) + 1));
	if (!ptr)
		return (NULL);
	j = 0;
	while (*s)
	{
		if (*s++ != c)
		{
			word_len = get_word_len(--s, c);
			ptr[j] = ft_substr(s, 0, word_len);
			if (!ptr[j++])
				return (ft_clear(ptr));
			s += word_len;
		}
	}
	return (ptr);
}
