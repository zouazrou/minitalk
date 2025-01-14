#include "minitalk.h"
void		is_nb(char *arg)
{
	if (!*arg)
	{
		printf("error : PID is empty !\n");
		exit(1);
	}
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
		{
			printf("error : PID is wrong !\n");
			exit(1);
		}
		arg++;
	}

}

void	check_args(int ac, char **av)
{
	if (ac != 3)
	{
		printf("error : number of arguments must be 3\n");
		exit(1);
	}
	is_nb(av[1]);
	if (!av[2][0])
	{
		printf("error : the message is empty !\n");
		exit(1);
	}
}
void	send_t_server(int pid, int dec)
{
	int num_of_byte;

	num_of_byte = 8;
	while (num_of_byte--)
	{
		if (!(dec % 2))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		dec /= 2;
		usleep(200);
	}
}
int	main(int ac, char **av)
{
	int		pid;
	int		dec;
	char	*msg;

	check_args(ac, av);
	pid = atoi(av[1]);
	msg = av[2];
	while (*msg)
	{
		dec = (int)*msg;
		send_t_server(pid, dec);
		msg++;
	}
	send_t_server(pid, 0);
	return(0);
}
