/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:11:40 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/08/05 15:35:10 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	num_of_words(char const *s, t_ms *ms)
{
	size_t	i;

	ms->quoteflag = 0;
	i = 0;
	while (*s)
	{
		ms_quoteflag(ms, *s);
		if (ms->quoteflag || (*s != ' ' && !ms->quoteflag))
		{
			i++;
			while (*s && (ms->quoteflag || (*s != ' ' && !ms->quoteflag)))
			{
				ms_quoteflag(ms, *s);
				s++;
			}
		}
		else
			s++;
	}
	return (i);
}

static size_t	get_word_len(char const *s, t_ms *ms)
{
	size_t	i;

	ms->quoteflag = 0;
	i = 0;
	while (*s && (ms->quoteflag || (*s != ' ' && !ms->quoteflag)))
	{
		ms_quoteflag(ms, *s);
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

char	**ft_split_quote(char const *s, t_ms *ms)
{
	char	**ptr;
	size_t	word_len;
	size_t	j;

	ptr = ft_calloc(sizeof(*ptr), (num_of_words(s, ms) + 1));
	if (!ptr)
		return (NULL);
	j = 0;
	while (*s)
	{
		ms_quoteflag(ms, *s);
		if ((*s++ != ' ' && !ms->quoteflag) || ms->quoteflag)
		{
			word_len = get_word_len(--s, ms);
			ptr[j] = ft_substr(s, 0, word_len);
			if (!ptr[j++])
				return (ft_clear(ptr));
			s += word_len;
		}
	}
	return (ptr);
}
