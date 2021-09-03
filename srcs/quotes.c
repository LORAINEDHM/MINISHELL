/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:49:17 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:49:18 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	ms_quoteflag(t_ms *ms, char c)
{
	if (c == '\'')
	{
		if (!(S_Q & ms->quoteflag) && !(D_Q & ms->quoteflag))
			ms->quoteflag |= S_Q;
		else
			ms->quoteflag &= 0b111111110;
	}
	else if (c == '"')
	{
		if (!(D_Q & ms->quoteflag) && !(S_Q & ms->quoteflag))
			ms->quoteflag |= D_Q;
		else
			ms->quoteflag &= 0b11111101;
	}
	return (ms->quoteflag);
}

void	ms_remove_quotes(t_ms *ms, char *token)
{
	const size_t	token_len = ft_strlen(token);
	int				old_quoteflag;
	int				i;

	i = 0;
	ms->quoteflag = 0;
	while (token[i])
	{
		old_quoteflag = ms->quoteflag;
		ms_quoteflag(ms, token[i]);
		if (old_quoteflag != ms->quoteflag)
			ft_memcpy(token + i, token + i + 1,
				token_len - i + 1);
		else
			i++;
	}
}
