/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:48:54 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:48:55 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_free_tokenlist(t_token **token)
{
	t_token	*temp;

	while (*token != NULL)
	{
		if ((*token)->content != NULL)
		{
			ms_free_and_init(&(*token)->content);
			temp = (*token)->next;
			free(*token);
			*token = temp;
		}
	}
}

void	ms_free_all_lists(t_ms *ms)
{
	t_allcmd	*temp;

	while (ms->first_cmd != NULL)
	{
		if (ms->first_cmd->cmd != NULL)
			ms_free_and_init(&ms->first_cmd->cmd);
		if (ms->inputdata != NULL)
			ms_free_and_init(&ms->inputdata);
		ms_free_tokenlist(&ms->first_cmd->inputf);
		ms_free_tokenlist(&ms->first_cmd->dinputf);
		ms_free_tokenlist(&ms->first_cmd->outputf);
		ms_free_tokenlist(&ms->first_cmd->doutputf);
		ms_free_tokenlist(&ms->first_cmd->argf);
		ms_free_tokenlist(&ms->first_cmd->varf);
		temp = ms->first_cmd->next;
		free(ms->first_cmd);
		ms->first_cmd = temp;
	}
	ms->last_cmd = NULL;
}

void	ms_free_and_init_dtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ms_free_and_init(char **str)
{
	free(*str);
	*str = NULL;
}
