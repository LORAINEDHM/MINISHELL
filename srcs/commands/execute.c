/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:47:48 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 21:52:06 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_count_args(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

static char	**ms_list_to_tab(t_token *args, t_allcmd *allcmd, t_ms *ms)
{
	unsigned int	i;
	char			**tab;

	if (allcmd)
		tab = malloc(sizeof(char *) * (ms_count_args(args) + 2));
	else
		tab = malloc(sizeof(char *) * (ms_count_args(args) + 1));
	if (!tab)
	{
		error_msg(-1, strerror(errno), ms);
		return (tab);
	}
	i = 0;
	if (allcmd)
		tab[i++] = allcmd->cmdpath;
	while (args)
	{
		tab[i++] = args->content;
		args = args->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	apply_cmd(char **tab, char **env, t_ms *ms, t_allcmd *allcmd)
{
	signal(SIGQUIT, ft_sigquit);
	g_env.g_pid = fork();
	if (g_env.g_pid == -1)
		return (error_msg(-1, strerror(errno), ms));
	if (!g_env.g_pid)
	{
		if ((!allcmd->i_type && allcmd->next && dup2(ms->fd_pipe, 0) == -1)
			 || close(ms->fd_pipe) == -1)
			error_msg(-1, strerror(errno), ms);
		execve(allcmd->cmdpath, tab, env);
		error_msg(-1, strerror(errno), ms);
		exit(126);
	}
	wait(&g_env.g_pid);
	ms->last_output = WEXITSTATUS(g_env.g_pid);
	g_env.g_pid = -1;
}

void	ms_execve(t_ms *ms, t_allcmd *allcmd)
{
	char	**args;
	char	**env;

	if (ms_path(ms, allcmd->cmd, allcmd))
	{
		args = ms_list_to_tab(allcmd->argf, allcmd, ms);
		if (args)
		{
			env = ms_list_to_tab(ms->env_first, 0, ms);
			if (env)
			{
				apply_cmd(args, env, ms, allcmd);
				free(env);
			}
			free(args);
		}
	}
	if (allcmd->cmdpath)
		ms_free_and_init(&allcmd->cmdpath);
}
