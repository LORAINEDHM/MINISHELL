/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:48:27 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:49:45 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_remove_print(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putstr_fd("\b", 1);
		++i;
	}
	i = 0;
	while (i < n)
	{
		ft_putstr_fd(" ", 1);
		++i;
	}
	i = 0;
	while (i < n)
	{
		ft_putstr_fd("\b", 1);
		++i;
	}
}

void	ft_sigint(int n)
{
	signal(n, ft_sigint);
	g_env.is_ctrl = 1;
	g_env.output_ctrls = 130;
	if (g_env.g_pid != -1)
	{
		kill(g_env.g_pid, SIGINT);
		if (g_env.fd_out != -1 && dup2(g_env.fd_out, 1) != -1)
			close(g_env.fd_out);
		g_env.fd_out = -1;
	}
	write(1, "\n", 1);
	if (g_env.g_pid == -1)
	{
		if (g_env.heredoc)
		{
			g_env.fd_heredoc = dup(STDIN_FILENO);
			close(STDIN_FILENO);
		}
		else
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	ft_sigquit(int n)
{
	(void) n;
	g_env.is_ctrl = 1;
	if (g_env.g_pid != -1)
	{
		kill(g_env.g_pid, SIGQUIT);
		ft_putstr_fd("Quit: 3", 1);
		ft_putchar_fd('\n', 1);
		g_env.output_ctrls = 131;
	}
}
