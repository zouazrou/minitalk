/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:28:08 by zouazrou          #+#    #+#             */
/*   Updated: 2025/01/16 20:31:57 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		dec /= 2;
		usleep(100);
	}
}

int	main(int ac, char **av)
{
	int		pid;
	int		dec;
	char	*msg;

	check_args(ac, av);
	pid = atoi(av[1]);
	if (kill(pid, 0) == -1)
		exit((ft_putstr_fd("error : PID invalid\n", 1), 1));
	msg = av[2];
	while (*msg)
	{
		dec = *msg;
		send_t_server(pid, dec);
		msg++;
	}
	send_t_server(pid, 0);
	return (0);
}
