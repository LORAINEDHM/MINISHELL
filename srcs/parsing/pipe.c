/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:48:39 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:48:40 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_empty_tab(t_ms *ms, char c, char *line)
{
	int		counter;
	char	quoteflag;
	char	**tab;

	counter = 1;
	while (*line)
	{
		quoteflag = ms_quoteflag(ms, *line);
		if (*line++ == c && !(S_Q & quoteflag) && !(D_Q & quoteflag))
			counter++;
	}
	ms->tab_size = counter;
	tab = ft_calloc(sizeof(char *), (counter + 1));
	if (!tab)
		error_msg(-1, strerror(errno), ms);
	return (tab);
}

static int	ms_fill_tab(t_ms *ms, t_pipe *pipe, char *line, int *i)
{
	int	k;

	if (!*(line + 1)
		|| (*line == '|' && !(S_Q & ms->quoteflag) && !(D_Q & ms->quoteflag)))
	{
		k = 1;
		if (*line == '|')
		{
			pipe->split_flag = 1;
			k = 0;
		}
		ms->tab[*i] = ft_substr(line - pipe->index, 0, pipe->index + k);
		if (!ms->tab[*i])
		{
			error_msg(-1, strerror(errno), ms);
			ms_free_and_init_dtab(ms->tab);
			return (0);
		}
		(*i)++;
	}
	return (1);
}

char	**ms_pipe_split(t_ms *ms, char *line)
{
	t_pipe	pipe;
	int		i;

	i = 0;
	pipe = (t_pipe){};
	ms->quoteflag = 0;
	ms->tab = create_empty_tab(ms, '|', line);
	if (!ms->tab)
		return (NULL);
	while (*line)
	{
		if (pipe.split_flag)
		{
			pipe.index = 0;
			ms->quoteflag = 0;
		}
		pipe.split_flag = 0;
		ms_quoteflag(ms, *line);
		if (!ms_fill_tab(ms, &pipe, line++, &i))
			return (NULL);
		pipe.index++;
	}
	return (ms->tab);
}
