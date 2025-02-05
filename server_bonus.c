/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:28:42 by zouazrou          #+#    #+#             */
/*   Updated: 2025/01/18 10:31:23 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int		g_byte = 0;

void	print_byte(char c)
{
	if (!c)
		ft_putchar_fd('\n', 1);
	ft_putchar_fd(c, 1);
	g_byte = 0;
}

void	handler(int sig, siginfo_t *info, void *more_info)
{
	pid_t		client;
	static char	c;

	(void)more_info;
	client = info->si_pid;
	g_byte++;
	c <<= 1;
	if (sig == SIGUSR1)
		c |= 0;
	else if (sig == SIGUSR2)
		c |= 1;
	if (g_byte == 8)
	{
		print_byte(c);
		if (!c)
			kill(client, SIGUSR2);
	}
	kill(client, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &act, NULL) == -1 || sigaction(SIGUSR2, &act,
			NULL) == -1)
		exit((ft_putstr_fd("error : sigaction\n", 1), 1));
	ft_putstr_fd("----------------------------\n", 1);
	ft_putstr_fd("---->|PID	:", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("|<----\n", 1);
	ft_putstr_fd("----------------------------\n", 1);
	g_byte = 0;
	while (1)
		;
	return (0);
}
// -Wall -Wextra -Werror
