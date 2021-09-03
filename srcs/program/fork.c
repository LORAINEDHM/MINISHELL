/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 18:05:06 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/04 15:41:06 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_parent(t_allcmd *allcmd, int fd[2], t_ms *ms)
{
	int	exit_child;

	wait(&exit_child);
	close(fd[1]);
	ms->fd_pipe = dup(fd[0]);
	close(fd[0]);
	if (!exit_child || allcmd == ms->last_cmd)
	{
		if (!allcmd->cmd)
			update_var(ms, allcmd->varf);
		if (ms_redirections(ms, allcmd) && allcmd->cmd)
			ms_builtins(ms, allcmd);
	}
	dup2(g_env.fd_in, 0);
	dup2(g_env.fd_out, 1);
}

static void	ms_child(t_allcmd *allcmd, int fd[2], t_ms *ms)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	if (allcmd->next == NULL)
		exit(0);
	else
		ms_fork(allcmd->next, ms);
	exit(ms->last_output);
}

void	ms_fork(t_allcmd *allcmd, t_ms *ms)
{
	pid_t	pid;
	int		fd[2];

	if (!allcmd->cmd && !allcmd->dinputf
		&& !allcmd->inputf && !allcmd->varf)
		return ;
	if (pipe(fd) == -1)
		return (error_msg(-1, strerror(errno), ms));
	pid = fork();
	if (pid == -1)
		return (error_msg(-1, strerror(errno), ms));
	else if (!pid)
		ms_child(allcmd, fd, ms);
	else
		ms_parent(allcmd, fd, ms);
}
