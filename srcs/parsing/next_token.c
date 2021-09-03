/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 09:41:26 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/04 09:19:05 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_copying_tokens(t_ms *ms, char *line, char **token)
{
	ms->quoteflag = 0;
	while (*line
		&& (ms->quoteflag || (!ft_strchr(" <>", *line) && !ms->quoteflag)))
	{
		ms_quoteflag(ms, *line);
		ms->index++;
		line++;
	}
	*token = ft_substr(line - ms->index, 0, ms->index);
	if (!*token)
	{
		error_msg(-1, strerror(errno), ms);
		return (0);
	}
	ms_dollar(ms, token);
	return (line);
}

char	*ms_get_next_token(t_ms *ms, char *line)
{
	char	*token;

	ms->index = 0;
	token = NULL;
	while (*line == ' ')
		line++;
	if (ft_strchr("<>&|", *line) || !*line)
	{
		ms->last_output = 2;
		error_msg(SYNTAX_ERROR, line, ms);
		return (0);
	}
	line = ms_copying_tokens(ms, line, &token);
	if (line && ms_token_to_struct(ms, ms->allcmd, token))
		return (line);
	return (0);
}
