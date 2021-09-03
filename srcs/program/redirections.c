/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 11:40:31 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/04 15:49:16 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(t_ms *ms, char *path, int o_flag, mode_t mode)
{
	char	*str;
	int		fd;

	if (*path == '/')
		str = strdup(path);
	else
		str = ms_join_path(ms->cd, path);
	if (!str)
	{
		error_msg(-1, strerror(errno), ms);
		return (-1);
	}
	fd = open(str, o_flag, mode);
	free(str);
	if (fd == -1)
	{
		ms->last_output = 1;
		error_msg(I_REDIRECTION_ERROR, path, ms);
		return (-1);
	}
	return (fd);
}

static int	ms_i_redirection(t_ms *ms, t_token *input, int flag, int last)
{
	int	fd;

	while (input)
	{
		if (flag == S_CHEVRON)
			fd = get_fd(ms, input->content, O_RDONLY, 0);
		else
			fd = get_fd(ms, HEREDOC, O_RDONLY, 0);
		if (fd == -1)
			return (0);
		if (!input->next && flag == last)
			dup2(fd, 0);
		close(fd);
		input = input->next;
	}
	return (1);
}

static int	ms_o_redirection(t_ms *ms, t_token *output, int flag, int last)
{
	int	fd;

	while (output)
	{
		fd = get_fd(ms, output->content, O_WRONLY | O_CREAT | flag, 0644);
		if (fd == -1)
			return (0);
		if (!output->next && last == flag)
			dup2(fd, 1);
		close (fd);
		output = output->next;
	}
	return (1);
}

int	ms_redirections(t_ms *ms, t_allcmd *allcmd)
{
	g_env.fd_in = dup(0);
	g_env.fd_out = dup(1);
	return (ms_all_id_redirection(ms, allcmd->dinputf)
		&& ms_i_redirection(ms, allcmd->inputf, S_CHEVRON, allcmd->i_type)
		&& ms_i_redirection(ms, allcmd->dinputl, D_CHEVRON, allcmd->i_type)
		&& ms_o_redirection(ms, allcmd->outputf, S_CHEVRON, allcmd->o_type)
		&& ms_o_redirection(ms, allcmd->doutputf, D_CHEVRON, allcmd->o_type));
}
