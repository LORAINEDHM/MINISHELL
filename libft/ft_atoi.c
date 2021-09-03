/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:05:37 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/05 16:40:13 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				sign;
	unsigned long	limit;

	result = 0;
	limit = __LONG_MAX__ / 10;
	sign = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (ft_isdigit(*str))
	{
		if ((result == limit && (*str - '0') > 6 - sign) || result > limit)
			return (-sign - 1);
		result = result * 10 + *str++ - '0';
	}
	if (sign)
		return (result * sign);
	return (result);
}
