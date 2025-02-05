/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 11:57:50 by zouazrou          #+#    #+#             */
/*   Updated: 2025/01/18 11:58:16 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

double	ft_pow(double base, int exponent)
{
	double	result;
	int		i;

	i = 0;
	result = 1.0;
	if (exponent < 0)
	{
		base = 1 / base;
		exponent = -exponent;
	}
	while (i < exponent)
	{
		result *= base;
		i++;
	}
	return (result);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else if (n >= 0 && n <= 9)
	{
		ft_putchar_fd(n + '0', fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	is_nb(char *arg)
{
	if (!*arg)
	{
		ft_putstr_fd("error : PID is empty !\n", 1);
		exit(1);
	}
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
		{
			ft_putstr_fd("error : PID is wrong !\n", 1);
			exit(1);
		}
		arg++;
	}
}
