/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:48:47 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:48:48 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_redirection(t_ms *ms, char *line)
{
	if (*line == '<')
	{
		if (*(line + 1) == '<')
		{
			line++;
			ms->tokenflag |= DINPUT;
		}
		else
			ms->tokenflag |= INPUT;
	}
	else
	{
		if (*(line + 1) == '>')
		{
			line++;
			ms->tokenflag |= DOUTPUT;
		}
		else
			ms->tokenflag |= OUTPUT;
	}
	line++;
	return (line);
}

static char	*save_token_into_list(t_ms *ms, char *line, char *cmd_flag)
{
	int	sign;

	if (!*line)
		return (0);
	else if (*line == '<' || *line == '>')
		line = ms_redirection(ms, line);
	else if (*cmd_flag == 0)
	{
		if (ms_get_index(line, &sign) > 0)
			ms->tokenflag |= VAR;
		else
		{
			ms->tokenflag |= CMD;
			*cmd_flag = 1;
		}
	}
	else
		ms->tokenflag |= ARG;
	line = ms_get_next_token(ms, line);
	return (line);
}

static int	ms_fill_allcmd(t_ms *ms, int i, char *line)
{
	char	cmd_flag;

	cmd_flag = 0;
	while (*line == ' ')
		line++;
	if (!*line && i != ms->tab_size - 1)
	{
		ms->last_output = 2;
		error_msg(SYNTAX_ERROR, "|", ms);
		return (0);
	}
	while (*line)
	{
		ms->tokenflag = 0;
		line = save_token_into_list(ms, line, &cmd_flag);
		if (!line)
			return (0);
		while (*line == ' ')
			line++;
	}
	return (1);
}

void	ms_add_to_allcmd_list(int *first_flag, t_ms *ms, t_allcmd *new_allcmd)
{
	if (*first_flag == 1)
	{
		new_allcmd->next = ms->allcmd;
		new_allcmd->next->previous = new_allcmd;
		ms->allcmd = new_allcmd;
	}
	else
	{
		ms->allcmd = new_allcmd;
		*first_flag = 1;
		ms->last_cmd = ms->allcmd;
	}
	ms->first_cmd = ms->allcmd;
}

int	ms_split_in_tokens(t_ms *ms)
{
	t_allcmd	*new_allcmd;
	int			first_flag;
	int			i;

	i = 0;
	first_flag = 0;
	while (ms->tab[i])
	{
		new_allcmd = ft_calloc(sizeof(t_allcmd), 1);
		if (!new_allcmd)
			return (0);
		ms_add_to_allcmd_list(&first_flag, ms, new_allcmd);
		if (ms_fill_allcmd(ms, i, ms->tab[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
