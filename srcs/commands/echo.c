/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst.student@19.be>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 13:44:33 by tvanelst          #+#    #+#             */
/*   Updated: 2021/07/30 15:22:42 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_check_n_option(t_token *args, char *flag_n)
{
	int	i;

	if (!ft_strncmp("-n", args->content, 2))
	{
		i = 2;
		while (args->content[i] == 'n')
			i++;
		if (!args->content[i])
		{
			*flag_n = 1;
			return (1);
		}
	}
	return (0);
}

void	ms_echo(t_ms *ms, t_token *args)
{
	char	flag_n;

	flag_n = 0;
	while (args && ms_check_n_option(args, &flag_n))
		args = args->next;
	while (args)
	{
		ft_putstr(args->content);
		args = args->next;
		if (args)
			ft_putstr(" ");
	}
	if (!flag_n)
		ft_putstr("\n");
	ms->last_output = 0;
}
