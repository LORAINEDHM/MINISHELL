/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:48:57 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:48:58 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_init_env_list(t_ms *ms, char *envp[])
{
	int		shlvl;
	char	*str;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "SHLVL=", 6))
		{
			shlvl = ft_atoi(ft_strrchr(*envp++, '=') + 1) + 1;
			str = ft_itoa(shlvl);
			if (!str)
				error_msg(-1, strerror(errno), ms);
			if (!ms_add_last(ft_strjoin("SHLVL=", str), ms,
					&ms->env_first, &ms->env_last))
				exit(1);
			free(str);
		}
		else if (!ms_add_last(ft_strdup(*envp++), ms,
				&ms->env_first, &ms->env_last))
			exit(1);
	}
}

void	ms_init_cmd(t_ms *ms)
{
	*ms = (t_ms){};
	if (!getcwd(ms->cd, PATH_MAX + 1))
		error_msg(-1, strerror(errno), ms);
	g_env.g_pid = -1;
}
