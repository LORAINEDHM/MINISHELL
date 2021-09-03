/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedison <timothyedison@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 15:29:23 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/04 16:35:39 by tedison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_token_to_struct2(t_ms *ms, t_allcmd *cmd, char *content)
{
	char	**my_split;
	int		i;

	i = 0;
	my_split = ft_split_quote(content, ms);
	free(content);
	if (!my_split)
		return (0);
	if (CMD & ms->tokenflag && my_split[i])
	{
		ms_remove_quotes(ms, my_split[i]);
		ms->allcmd->cmd = my_split[i++];
	}
	while (my_split[i])
	{
		if (!ms_add_last(my_split[i++], ms, &cmd->argf, &cmd->argl))
		{
			while (my_split[i - 1])
				free(my_split[i++]);
			free(my_split);
			return (0);
		}
	}
	free(my_split);
	return (1);
}

int	ms_token_to_struct(t_ms *ms, t_allcmd *cmd, char *content)
{
	if (VAR & ms->tokenflag)
		return (ms_add_last(content, ms, &cmd->varf, &cmd->varl));
	else if (INPUT & ms->tokenflag)
	{
		ms->allcmd->i_type = S_CHEVRON;
		return (ms_add_last(content, ms, &cmd->inputf, &cmd->inputl));
	}
	else if (DINPUT & ms->tokenflag)
	{
		ms->allcmd->i_type = D_CHEVRON;
		return (ms_add_last(content, ms, &cmd->dinputf, &cmd->dinputl));
	}
	else if (OUTPUT & ms->tokenflag)
	{
		ms->allcmd->o_type = S_CHEVRON;
		return (ms_add_last(content, ms, &cmd->outputf, &cmd->outputl));
	}
	else if (DOUTPUT & ms->tokenflag)
	{
		ms->allcmd->o_type = D_CHEVRON;
		return (ms_add_last(content, ms, &cmd->doutputf, &cmd->doutputl));
	}
	return (ms_token_to_struct2(ms, cmd, content));
}
