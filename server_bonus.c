/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zouazrou <zouazrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:28:42 by zouazrou          #+#    #+#             */
/*   Updated: 2025/02/06 11:35:12 by zouazrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

typedef struct byte
{
	int		idx_byte;
	pid_t	curr_pid;
}			t_byte;

t_byte	g_byte;

void	print_byte(char c)
{
	if (!c)
		ft_putchar_fd('\n', 1);
	ft_putchar_fd(c, 1);
	g_byte.idx_byte = 0;
}

void	reinitializing(pid_t new_client)
{
	g_byte.idx_byte = 0;
	g_byte.curr_pid = new_client;
}

void	handler(int sig, siginfo_t *info, void *more_info)
{
	pid_t		sig_pid;
	static char	c;

	(void)more_info;
	sig_pid = info->si_pid;
	if (sig_pid != g_byte.curr_pid)
		reinitializing(sig_pid);
	g_byte.idx_byte++;
	c <<= 1;
	if (sig == SIGUSR1)
		c |= 0;
	else if (sig == SIGUSR2)
		c |= 1;
	if (g_byte.idx_byte == 8)
	{
		print_byte(c);
		if (!c)
			kill(sig_pid, SIGUSR2);
	}
	kill(sig_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) == -1 || sigaction(SIGUSR2, &act,
			NULL) == -1)
		exit((ft_putstr_fd("error : sigaction\n", 1), 1));
	ft_putstr_fd("----------------------------\n", 1);
	ft_putstr_fd("---->|PID	:", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("|<----\n", 1);
	ft_putstr_fd("----------------------------\n", 1);
	g_byte.idx_byte = 0;
	g_byte.curr_pid = -1;
	while (1)
		;
	return (0);
}
// -Wall -Wextra -Werror
