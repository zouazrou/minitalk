/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:28:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/02/06 11:44:41 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int		g_ready = 0;

void	ready(int sig)
{
	if (sig == SIGUSR1)
		g_ready = 1337;
	else if (sig == SIGUSR2)
		exit((ft_putstr_fd("Message received \n", 1), 0));
}

void	check_args(int ac, char **av)
{
	if (ac != 3)
	{
		ft_putstr_fd("error : number of arguments must be 3\n", 1);
		exit(1);
	}
	is_nb(av[1]);
	if (!av[2][0])
	{
		ft_putstr_fd("error : the message is empty !\n", 1);
		exit(1);
	}
}

void	send_t_server(pid_t pid, char c)
{
	int	num_of_byte;

	num_of_byte = 8;
	while (num_of_byte--)
	{
		if (((c >> num_of_byte) % 2) == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				exit((ft_putstr_fd("error : when send SIGUSR1\n", 1), 1));
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit((ft_putstr_fd("error : when send SIGUSR2\n", 1), 1));
		}
		while (!g_ready)
			;
		g_ready = 0;
	}
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	sign;

	i = 0;
	nb = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (nb * sign);
}

int	main(int ac, char **av)
{
	pid_t		pid;
	char		*msg;

	check_args(ac, av);
	msg = av[2];
	pid = ft_atoi(av[1]);
	if (kill(pid, 0) == -1)
		exit((ft_putstr_fd("error : PID invalid\n", 1), 1));
	signal(SIGUSR1, ready);
	signal(SIGUSR2, ready);
	while (*msg)
	{
		send_t_server(pid, *msg);
		msg++;
	}
	send_t_server(pid, '\0');
	while (1949)
		pause();
	return (0);
}
