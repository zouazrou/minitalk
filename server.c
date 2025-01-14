#include "minitalk.h"


typedef	struct byte
{
	int	array[8];
	int	index;
}byte_t;

byte_t byte;

double ft_pow(double base, int exponent) {
    double result = 1.0;

    if (exponent < 0) {
        base = 1 / base;
        exponent = -exponent;
    }
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}
void	print_byte(void)
{
	int	dec;
	int	i;

	dec = 0;
	i = 7;
	while (i > -1)
	{
		if (byte.array[i] == 1)
			dec += ft_pow(2, 7 - i);
		i--;
	}
	if (!dec)
	{
		printf("\n");
	}
	printf("%c", (char)dec);
}
void	initialization(int bit)
{
	byte.array[byte.index] = bit;
	byte.index--;
}
void	handle_1(int sig)
{
	(void)sig;
	initialization(0);
}
void	handle_2(int sig)
{
	(void)sig;
	initialization(1);
}
int	main(void)
{
	struct sigaction act1;
	struct sigaction act2;

	act1.sa_handler = handle_1;
	act2.sa_handler = handle_2;
	act1.sa_flags = 0;
	act2.sa_flags = 0;
	sigaction(SIGUSR1, &act1, NULL);
	sigaction(SIGUSR2, &act2, NULL);
	printf("PID : %d\n", getpid());
	printf("-----------------------------\n");
	byte.index = 7;
	while (1)
	{
		pause();
		if (byte.index == -1)
		{
			print_byte();
			byte.index = 7;
		}
	}
	return (0);
}
