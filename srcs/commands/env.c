/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:48:04 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:48:05 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_env(t_ms *ms, t_token *env, char declare)
{
	int	i;

	while (env)
	{
		if (declare)
		{
			ft_putstr("declare -x ");
			i = 0;
			while (env->content[i] != '=')
				write(1, env->content + i++, 1);
			ft_putstr("=\"");
			ft_putstr(ft_strchr(env->content, '=') + 1);
			ft_putstr("\"\n");
		}
		else
			ft_putendl_fd(env->content, 1);
		env = env->next;
	}
	ms->last_output = 0;
}
