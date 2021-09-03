/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:48:36 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:48:37 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_parsing(t_ms *ms)
{
	int	ret;

	ret = (ms_pipe_split(ms, ms->line)
			&& ms_split_in_tokens(ms));
	if (ms->tab)
		ms_free_and_init_dtab(ms->tab);
	return (ret);
}
