/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:28:42 by zouazrou          #+#    #+#             */
/*   Updated: 2025/02/05 11:59:05 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

typedef struct byte
{
	int	array[8];
	int	index;
}		t_byte;

t_byte	g_byte;

void	print_byte(void)
{
	int	dec;
	int	i;

	dec = 0;
	i = 7;
	while (i > -1)
	{
		if (g_byte.array[i] == 1)
			dec += ft_pow(2, 7 - i);
		i--;
	}
	if (!dec)
		ft_putchar_fd('\n', 1);
	ft_putchar_fd(dec, 1);
}

void	initialization(int bit)
{
	g_byte.array[g_byte.index] = bit;
	g_byte.index--;
	if (g_byte.index == -1)
	{
		print_byte();
		g_byte.index = 7;
	}
}

void	handler(int sig, siginfo_t *info, void *more_info)
{
	pid_t	client;

	(void)more_info;
	client = info->si_pid;
	if (sig == SIGUSR1)
		initialization(0);
	else if (sig == SIGUSR2)
		initialization(1);
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
	g_byte.index = 7;
	while (1)
		;
	return (0);
}
// -Wall -Wextra -Werror
