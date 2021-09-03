/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:48:08 by tvanelst          #+#    #+#             */
/*   Updated: 2021/08/06 13:48:09 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	max_int_value(char *str)
{
	unsigned long long	n;
	char				sign;

	n = 0;
	sign = (*str == '-');
	if (sign)
		str++;
	while (*str)
	{
		n *= 10;
		n += *str++ - '0';
		if ((n > (unsigned long long)LLONG_MAX && !sign)
			|| (n > (unsigned long long)LLONG_MIN && sign))
			return (0);
	}
	return (1);
}

static int	all_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}

void	ms_exit(t_ms *ms, t_token *argf)
{
	ft_putstr_fd("exit\n", 1);
	if (argf == NULL)
		exit(0);
	if (!all_digit(argf->content) || !max_int_value(argf->content))
	{
		error_msg(NUMERIC_ARGUMENT_REQUIRED, argf->content, ms);
		ms->last_output = 2;
		exit(2);
	}
	if (argf->next == NULL)
		exit(ft_atoi(argf->content));
	else
	{
		ft_putstr("bash: exit: too many arguments\n");
		ms->last_output = 1;
	}
}
