/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedison <timothyedison@hotmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:50:33 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/03 18:13:58 by tedison          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd(t_ms *ms, char *var)
{
	char	*content;

	if (ms_get_var_value(ms->env_first, var, ft_strlen(var) - 1))
	{
		content = ft_strjoin(var, ms->cd);
		if (!content)
			return (error_msg(-1, strerror(errno), ms));
		ms_export(ms, content, ft_strlen(var) - 1, 0);
		free(content);
	}
}

static void	regular_cd_with_path(t_ms *ms, t_allcmd *allcmd)
{
	set_pwd(ms, "OLDPWD=");
	if (chdir(allcmd->argf->content))
		return (error_msg(UNVALID_PATH, allcmd->argf->content, ms));
	if (!getcwd(ms->cd, PATH_MAX + 1))
	{	
		if (!ft_strncmp(allcmd->argf->content, ".", 2))
			error_msg(ERROR_RETRIEVING_CURRENT_DIRECTORY, NULL, ms);
		else
			error_msg(-1, strerror(errno), ms);
	}
	set_pwd(ms, "PWD=");
}

void	ms_cd(t_ms *ms, t_allcmd *allcmd)
{
	char	*buff;

	if (!allcmd->argf)
	{
		buff = ms_get_var_value(ms->env_first, "HOME", 4);
		if (!buff)
			return (error_msg(HOME_NOT_SET, "cd: ", ms));
		set_pwd(ms, "OLDPWD=");
		if (chdir(buff))
			return (error_msg(-1, strerror(errno), ms));
		ft_memccpy(ms->cd, buff, 0, PATH_MAX + 1);
		set_pwd(ms, "PWD=");
	}
	else if (allcmd->argf->next)
		return (error_msg(TOO_MANY_ARGS, "cd: ", ms));
	else
		regular_cd_with_path(ms, allcmd);
	ms->last_output = 0;
}
