/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 14:49:41 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/04 09:57:47 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_var(t_ms *ms, t_token *var)
{
	t_token	*token;
	int		index;
	int		sign;

	while (var)
	{
		token = NULL;
		index = ms_get_index(var->content, &sign);
		if (!get_var_name(ms, &token, var->content, index))
			break ;
		if (token)
			ms_export(ms, var->content, index, sign);
		var = var->next;
	}
}
