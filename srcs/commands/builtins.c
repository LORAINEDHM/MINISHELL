/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 14:48:14 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/02 14:14:58 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	low_case(char c)
{
	if ('A' <= c && c <= 'Z')
		c += 'a' - 'A';
	return (c);
}

static char	ft_no_case_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != low_case(s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ms_builtins(t_ms *ms, t_allcmd *allcmd)
{
	const char	*builtin = allcmd->cmd;
	const int	builtin_len = ft_strlen(builtin) + 1;

	if (!ft_strncmp("export", builtin, builtin_len))
		ms_export_unset(ms, allcmd->argf, ms_export);
	else if (!ft_strncmp("unset", builtin, builtin_len))
		ms_export_unset(ms, allcmd->argf, ms_unset);
	else if (!ft_strncmp("exit", builtin, builtin_len))
		ms_exit(ms, allcmd->argf);
	else if (!ft_strncmp("cd", builtin, builtin_len))
		ms_cd(ms, allcmd);
	else if (!ft_no_case_strncmp("cd", builtin, builtin_len))
		return (0);
	else if (!ft_no_case_strncmp("echo", builtin, builtin_len))
		ms_echo(ms, allcmd->argf);
	else if (!ft_no_case_strncmp("pwd", builtin, builtin_len))
		ms_pwd(ms);
	else if (!ft_no_case_strncmp("env", builtin, builtin_len))
		ms_env(ms, ms->env_first, 0);
	else
		ms_execve(ms, allcmd);
	return (0);
}
