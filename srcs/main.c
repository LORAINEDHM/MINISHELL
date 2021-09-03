/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:49:01 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:49:02 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_ctrl_d(t_ms *ms)
{
	int	tmp;

	tmp = ms->last_output;
	ft_putstr_fd("exit\n", 1);
	ms_free_tokenlist(&ms->env_first);
	exit(0);
}

static void	minishell(t_ms *ms)
{
	ms->line = readline("minishell> ");
	if (!ms->line)
		return (ms_ctrl_d(ms));
	if (*ms->line)
		add_history(ms->line);
	else
		return (free(ms->line));
	if (g_env.is_ctrl)
	{
		ms->last_output = g_env.output_ctrls;
		g_env.is_ctrl = 0;
	}
	if (ms_parsing(ms))
		ms_fork(ms->first_cmd, ms);
	ms_free_all_lists(ms);
	free(ms->line);
}

int	main(int ac, char *argv[], char *envp[])
{
	t_ms	ms;

	(void)ac;
	(void)*argv;
	ms_init_cmd(&ms);
	ms_init_env_list(&ms, envp);
	signal(SIGINT, ft_sigint);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		minishell(&ms);
	}
	return (0);
}
