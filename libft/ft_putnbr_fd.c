/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvanelst <tvanelst@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 21:11:31 by thomasvanel       #+#    #+#             */
/*   Updated: 2021/04/05 15:55:11 by tvanelst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0)
	{
		write(fd, "-", 1);
		c = -(n % -10) + '0';
		if (-n / 10)
			ft_putnbr_fd(-(n / 10), fd);
	}
	else if (!n)
	{
		write(fd, "0", 1);
		return ;
	}
	else
	{
		c = n % 10 + '0';
		if (n / 10)
			ft_putnbr_fd(n / 10, fd);
	}
	write(fd, &c, 1);
}
