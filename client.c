/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:28:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/02/05 11:56:14 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_ready = 0;

void	ready(int sig)
{
	(void)sig;
	g_ready = 1337;
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

void	send_t_server(int pid, int dec)
{
	int	num_of_byte;

	num_of_byte = 8;
	while (num_of_byte--)
	{
		if (!(dec % 2))
		{
			if (kill(pid, SIGUSR1) == -1)
				exit((ft_putstr_fd("error : when send SIGUSR1\n", 1), 1));
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				exit((ft_putstr_fd("error : when send SIGUSR2\n", 1), 1));
		}
		dec /= 2;
		while (!g_ready)
			;
		g_ready = 0;
	}
}

int	main(int ac, char **av)
{
	int		pid;
	char	*msg;

	check_args(ac, av);
	msg = av[2];
	pid = atoi(av[1]);
	if (kill(pid, 0) == -1)
		exit((ft_putstr_fd("error : PID invalid\n", 1), 1));
	signal(SIGUSR1, ready);
	while (*msg)
	{
		send_t_server(pid, *msg);
		msg++;
	}
	send_t_server(pid, '\0');
	return (0);
}
